import os
import telebot
import speech_recognition
from pydub import AudioSegment
from PIL import Image, ImageEnhance, ImageFilter
from random import *
import sqlite3 as sql
from bs4 import BeautifulSoup as bs
import requests
from googletrans import Translator

# Читаю информацию, которую нельзя оставлять при публикации на гитхаб
private_file = open('private_content.txt', 'r', encoding='utf8')
token = private_file.readline().split(' ')[0]  # Токен бота
boss_id = private_file.readline().split(' ')[0]  # мой id
boss_teg = private_file.readline().split(' ')[0]  # мой тег (@userteg)
bandchat_id = private_file.readline().split(' ')[0]  # id чата банды
bandchatmembers_info = private_file.read()  # Информация о членах чата банды
private_file.close()

bot = telebot.TeleBot(token)

# Флаги, которые нужны для обработки команд
adding_a_quote_flag = False
poetry_flag = False
get_info_flag = False
add_user_flag = False
change_me_flag = False
translate_flag = False

'''
def transform_image(filename):
    # Функция обработки изображения
    source_image = Image.open(filename)
    enhanced_image = source_image.filter(ImageFilter.EMBOSS)
    enhanced_image = enhanced_image.convert('RGB')
    enhanced_image.save(filename)
    return filename


@bot.message_handler(content_types=['photo'])
def resend_photo(message):
    # Функция отправки обработанного изображения
    file_id = message.photo[-1].file_id
    filename = download_file(bot, file_id)

    # Трансформируем изображение
    transform_image(filename)

    image = open(filename, 'rb')
    bot.send_photo(message.chat.id, image)
    image.close()

    # Не забываем удалять ненужные изображения
    if os.path.exists(filename):
        os.remove(filename)
'''


def oga2wav(filename):
    # Конвертация формата файлов
    new_filename = filename.replace(".oga", ".wav")
    audio = AudioSegment.from_file(filename)
    audio.export(new_filename, format="wav")
    return new_filename


def recognize_speech(oga_filename):
    # Перевод голоса в текст + удаление использованных файлов
    wav_filename = oga2wav(oga_filename)
    recognizer = speech_recognition.Recognizer()

    with speech_recognition.WavFile(wav_filename) as source:
        wav_audio = recognizer.record(source)

    text = recognizer.recognize_google(wav_audio, language="ru")

    if os.path.exists(oga_filename):
        os.remove(oga_filename)

    if os.path.exists(wav_filename):
        os.remove(wav_filename)

    return text


def download_file(bot, file_id):
    # Скачивание файла, который прислал пользователь
    file_info = bot.get_file(file_id)
    downloaded_file = bot.download_file(file_info.file_path)
    filename = file_id + file_info.file_path
    filename = filename.replace("/", "_")
    with open(filename, "wb") as f:
        f.write(downloaded_file)
    return filename


@bot.message_handler(commands=["hey"])
def say_hi(message):
    if message.from_user.id == boss_id:
        bot.send_message(
            message.chat.id, f"доброе утро, шеф!"
        )
    else:
        bot.send_message(
            message.chat.id, f"{message.from_user.first_name} banned. Say bye to him"
        )
    # New Year edition
    # if message.from_user.id == boss_id:
    #     bot.send_message(
    #     message.chat.id, f"С новой годой, говнокодер"
    #     )
    # else:
    #     bot.send_message(
    #         message.chat.id, f"С новой годой, {message.from_user.first_name}!! :)"
    #     )


@bot.message_handler(commands=["quote"])
def reply(message):
    list_w_quotes = []
    with open('quotes.txt', 'r', encoding='utf8') as file_w_quotes:
        s = file_w_quotes.readlines()
    for quote in s:
        list_w_quotes.append(quote)

    bot.send_message(message.chat.id, f"{choice(list_w_quotes)}\n(с) Jason Statham")


@bot.message_handler(commands=["member_list"])
def reply(message):
    if message.chat.id == int(bandchat_id):  # чат с друзьями Bollywood
        if message.from_user.id == boss_id:
            bot.send_message(
                message.chat.id, f"отправляю, шеф"
            )
        bot.send_message(
            message.chat.id,
            bandchatmembers_info
        )
    else:
        bot.send_message(
            message.chat.id, f"доступно только в группе"
        )


# если после вызова poetry не ввели номер, а вызвали
# следующую команду, он забывает про poetry,
# так что отключать флаги не надо

@bot.message_handler(commands=["poetry"])  # стишок на выбранную тему
def reply(message):
    # вход в команду
    global poetry_flag
    poetry_flag = True
    with open('names_categories.txt', 'r') as file:
        m = file.read()
    bot.send_message(
        message.chat.id, m
    )  # отправляем пользователю список имён/праздников
    bot.send_message(
        message.chat.id, f'Могу предложить вам стихотворения по такми темам. '
                         f'Отправьте номер выбранной темы в ответ'
    )
    # дальше в content_types=["text"]

    # выход из команды
    # poetry_flag = False


# отключил. На постоянке она не нужна. Хочешь добавить цитат - включай, добавляй и отключай вновь
'''@bot.message_handler(commands=["addind_a_quote"])  # добавить цитату
def reply(message):
    # вход в команду
    global adding_a_quote_flag
    adding_a_quote_flag = True
    bot.send_message(message.chat.id, f'Какую цитату добавить в список?')
    # дальше в content_types=["text"]

    # выход из команды
    # adding_a_quote_flag = False'''


@bot.message_handler(commands=["call_developer"])  # написать разрабу
def reply(message):
    bot.send_message(
        message.chat.id, f'тег разработчика: {boss_teg}\nмогу подсказать, с чего начать:\n'
                         f'"привет, Миша! Когда выйдешь на работу?.."'
    )


class DataBaseClass(object):
    @staticmethod
    def add_user(info: str, my_username: str):
        connection = sql.connect('database_bot.db')
        cursor = connection.cursor()
        error = f'Что-то пошло не по плану...\nПожалуйста, сообщите разработчику {boss_teg} об ошибке'
        data = [x for x in info.split('\n')]
        try:
            cursor.execute('INSERT OR REPLACE INTO Users (id, username, fullname, phone, birthdate, contactslist) '
                           'VALUES(?, ?, ?, ?, ?, ?)',
                           (int(data[0]), data[1], data[2], data[3], data[4], data[5]))
            error = 'Пользователь успешно добавлен!'
        except Exception as e:
            error = 'Не удалось добавить пользователя. Пожалуйста, введите все перечисленные параметры, каждый с новой строки'

        finally:
            connection.commit()
            connection.close()
            return error

    @staticmethod
    def change_me(info: str, my_username: str):
        connection = sql.connect('database_bot.db')
        cursor = connection.cursor()

        error, my_id = DataBaseClass.get_id(my_username, my_username)
        if error != 'ok':
            return error
        data = list([x for x in info.split('\n')])
        data.insert(0, int(my_id))

        if data[1] == my_username:
            try:
                cursor.execute(f'insert or replace into Users'
                               f'(id, username, name, birthdate)'
                               f'VALUES({my_id}, "{data[1]}", "{data[2]}", "{data[3]}")')

                error = 'Изменено успешно!'
            except sql.Error as e:
                error = ('Не удалось обновить пользователя. '
                         'Пожалуйста, введите все перечисленные параметры, каждый с новой строки')

            finally:
                connection.commit()
                connection.close()
        else:
            error = ('Кажется, это не вы (у вас другое имя пользователя в телеграме). '
                     'Вы можете изменить информацию только о себе')

        return error

    @staticmethod
    def get_id(my_username: str, username: str):
        connection = sql.connect('database_bot.db')
        cursor = connection.cursor()
        error = 'ok'
        user_id = ''
        list_of_contacts = ''
        try:
            cursor.execute(f'select id from Users where username = "{username}"')
            user_id = str(cursor.fetchone())[1:-2]
            cursor.execute(f'select id from Users where username = "{my_username}"')
            my_id = str(cursor.fetchone())[1:-2]
            cursor.execute(f'select list_of_contacts from Contacts where id = "{my_id}"')
            list_of_contacts = list(str(cursor.fetchone())[2:-3].split())
        except sql.Error as e:
            error = 'Произошла ошибка во время извлечения информации'

        # anyway
        finally:
            connection.commit()
            connection.close()

        if user_id not in list_of_contacts and user_id + ',' not in list_of_contacts:
            error = 'Кажется, этот пользователь запретил вам просматривать информацию о нём'

        return error, user_id

    @staticmethod
    def get_info(my_username: str, username: str):
        info = ''

        error, user_id = DataBaseClass.get_id(my_username, username)
        if error != 'ok':
            return error, info

        connection = sql.connect('database_bot.db')
        cursor = connection.cursor()
        try:
            cursor.execute(f'select * from Users where id = "{user_id}"')
            info = list(cursor.fetchone())
        except sql.Error as e:
            error = 'Произошла ошибка во время извлечения информации'
        # anyway
        finally:
            connection.commit()
            connection.close()
            return error, info

    @staticmethod
    def get_list_of_my_contacts(message, my_username: str):
        connection = sql.connect('database_bot.db')
        cursor = connection.cursor()
        error = 'ok'
        answer = ''
        try:
            cursor.execute(f'select id from Users where username = "{my_username}"')
            my_id = str(cursor.fetchone())[1:-2]
        except Exception as e:  # если пользователя my_username нет в базе данных, то дальше программа идти не должна
            error = 'Не удалось найти пользователя с вашим телеграм-тегом'
            connection.commit()
            connection.close()
            return error, answer

        # если пользователь my_username есть в базе данных
        try:
            cursor.execute(f'select list_of_contacts from Contacts where id = "{int(my_id)}"')
            list_of_contacts = cursor.fetchone()
            list_of_contacts = str(list_of_contacts)[2:-3].split()

            for id_number in list_of_contacts:
                id_number = str(id_number).replace(',', '')
                cursor.execute(f'select username from Users where id = {int(id_number)}')
                username = cursor.fetchone()
                cursor.execute(f'select name from Users where id = {int(id_number)}')
                name = cursor.fetchone()
                answer += f'{str(name)[2:-3]} @{str(username)[2:-3]}' + '\n'
            return error, answer
        except Exception as e:
            error = 'Приносим извинения: произошла ошибка по время извлечения ваших контактов'
        finally:
            connection.commit()
            connection.close()
            return error, answer

    @staticmethod
    def get_my_info(my_username: str):
        error = 'ok'
        info = ''
        connection = sql.connect('database_bot.db')
        cursor = connection.cursor()
        try:
            cursor.execute(f'Select * from Users where username = "{my_username}"')
            info = cursor.fetchone()
            if info is None:
                error = 'Не удалось найти запись с вашим именем пользователя...'
            else:
                info = list(info)
        except sql.Error as e:
            error = 'Не удалось найти запись с вашим именем пользователя...'
        finally:
            connection.commit()
            connection.close()
            return error, info


@bot.message_handler(commands=["add_user"])  # добавить нового пользователя
def reply(message):
    global add_user_flag
    add_user_flag = True
    bot.send_message(message.chat.id, f'Введите информацию о пользователе, каждый пункт с новой строки. '
                                      f'Если не хотите что-то указывать, напишите "-" в соответствующей строке. '
                                      f'Строки: \nИдентификатор (число)\nТелеграм-тег\nИмя (фамилия, отчество)\n'
                                      f'Номер телефона\nДата рождения\nСписок знакомых (идентификаторы через пробел)')


@bot.message_handler(commands=["change_me"])  # изменить информацию о себе
def reply(message):
    global change_me_flag
    change_me_flag = True

    database = DataBaseClass()
    error, info = database.get_my_info(message.from_user.username)

    # если инфоррмация о пользователе извлеклась без ошибки
    if error == 'ok':
        bot.send_message(message.chat.id, f'Вот что известно про вас сейчас:\n'
                                          f'Телеграм: @{info[1]}\nЗовут: {info[2]}\n'
                                          f'Дата рождения: {info[3]}')

        bot.send_message(message.chat.id, f'Введите обновлённую информацию, каждый пункт с новой строки без цифр. '
                                          f'\nЕсли не хотите что-то указывать, напишите "-" в соответствующей строке. '
                                          f'Строки:\n1. Телеграм-тег\n2. Имя\n3. Дата рождения')
    # если при извлечении информации о пользователе возникла ошибка
    else:
        bot.send_message(message.chat.id, error)


@bot.message_handler(commands=["get_info"])  # получить информацию о контакте
def reply(message):
    global get_info_flag

    # попытка отправления запросившему списка доступных ему контактов
    database = DataBaseClass()
    error, info = database.get_list_of_my_contacts(message, str(message.from_user.username))

    if error == 'ok':  # если список контактов успешно извлечён
        bot.send_message(message.chat.id, f'Вот список ваших контактов:\n{info}')  # отправляются его контакты
        bot.send_message(message.chat.id,
                         f'Напишите в ответ телеграм-тег (@ перед ним писать не надо), данные которого хотите вспомнить')
    else:
        bot.send_message(massage.chat.id, error)

    # вход
    get_info_flag = True


@bot.message_handler(commands=["contacts_list"])  # список контактов запросившего
def reply(message):
    database = DataBaseClass()
    error, info = database.get_list_of_my_contacts(message, str(message.from_user.username))

    if error == 'ok':  # если список контактов успешно извлечён
        bot.send_message(message.chat.id, f'Вот список ваших контактов:\n{info}')
    else:
        bot.send_message(message.chat.id, error)


def translate_text(text: str):
    translator = Translator()
    assert isinstance(text, str)
    if text.isascii():
        translation = translator.translate(text, src='en', dest='ru')
        return translation.text
    else:
        translation = translator.translate(text, src='ru', dest='en')
        return translation.text


@bot.message_handler(commands=["translate"])  # переводчик хухл
def reply(message):
    global translate_flag
    translate_flag = True
    bot.send_message(message.chat.id, f'Какой текст перевести?')


@bot.message_handler(content_types=["text"])
def reply(message):
    message_text = str(message.text)
    global poetry_flag, adding_a_quote_flag, get_info_flag, add_user_flag, change_me_flag, translate_flag
    if False:
        pass

    elif poetry_flag:  # command == ["poetry"]
        if '1' <= message_text <= '271':  # valid number?
            i = int(message_text)
            with open('links_by_names_categories.txt', 'r') as file:
                links_list = file.read().split('\n')
            link = links_list[i - 1]
            r = requests.get(link)
            soup = bs(r.content, "html.parser")
            poetry_list = soup.find_all(class_='sfst')
            for poetry in poetry_list[:2]:
                bot.send_message(message.chat.id, poetry.text.
                                 replace('.', '.\n').
                                 replace('!', '!\n').
                                 replace('?', '?\n').
                                 replace(':', ':\n').
                                 replace(',', ', '))

            # выход из команды poetry
            poetry_flag = False

        else:
            bot.send_message(message.chat.id, f'Промазали по клавиатуре. Не отчаивайтесь!\n'
                                              f'Попробуйте снова :)\n'
                                              f'*Подсказка: номер - число из отрезка [1, 271]')

    elif adding_a_quote_flag:
        with open('quotes.txt', 'a', encoding='utf8') as file_w_quotes:
            file_w_quotes.write('\n' + message_text)

        bot.send_message(message.chat.id, f'done')
        # выход из команды poetry
        adding_a_quote_flag = False

    elif add_user_flag:
        database = DataBaseClass()
        result = database.add_user(message.text, str(message.from_user.username))
        bot.send_message(message.chat.id, f'{result}')

        add_user_flag = False

    elif change_me_flag:
        database = DataBaseClass()
        error = database.change_me(message.text, str(message.from_user.username))
        bot.send_message(message.chat.id, error)

        change_me_flag = False

    elif get_info_flag:
        database = DataBaseClass()
        error, info = database.get_info(str(message.from_user.username), message.text)
        if error == 'ok':
            bot.send_message(message.chat.id, f'Вот что известно про этого человека:\n'
                                              f'Телеграм-тег: @{info[1]}\nЗовут: {info[2]}\n'
                                              f'Дата рождения: {info[3]}\n')
        else:
            bot.send_message(message.chat.id, error)

        get_info_flag = False

    elif translate_flag:
        translated_text = translate_text(message.text)
        bot.send_message(message.chat.id, translated_text)

        translate_flag = False


@bot.message_handler(content_types=["voice"])
def transcript(message):
    # Функция, отправляющая текст в ответ на голосовое
    filename = download_file(bot, message.voice.file_id)
    text = recognize_speech(filename)
    bot.send_message(message.chat.id, text)


# Запускаем бота. Он будет работать, пока мы не остановим выполнение программы
bot.polling()
# bot.infinity_polling(timeout=10, long_polling_timeout = 5)
