import os
import telebot
import speech_recognition
from pydub import AudioSegment
from PIL import Image, ImageEnhance, ImageFilter
from random import *
import sqlite3 as sql
from bs4 import BeautifulSoup as bs
import requests

# ↓↓↓ Ниже нужно вставить токен, который дал BotFather при регистрации
# Пример: token = '2007628239:AAEF4ZVqLiRKG7j49EC4vaRwXjJ6DN6xng8'
token = ""  # <<< Ваш токен

bot = telebot.TeleBot(token)

adding_a_quote_flag = False
poetry_flag = False
get_info_flag = False
add_user_flag = False
change_me_flag = False
"""

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

"""


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
    if message.from_user.username == "...":
        bot.send_message(message.chat.id, f"доброе утро, шеф!")
    else:
        bot.send_message(
            message.chat.id, f"{message.from_user.first_name} banned. Say bye to him"
        )
    # New Year edition
    # if message.from_user.username == "...":
    #     bot.send_message(message.chat.id, f"С новой годой, говнокодер")
    # else:
    #     bot.send_message(
    #         message.chat.id, f"С новой годой, {message.from_user.first_name}!! :)"
    #     )


# @bot.message_handler(commands=["alexandr"])
# def reply(message):
#     bot.send_message(
#         message.chat.id,
#         f"Когда сильно я убитый — Александр (Александр)\n\
# Мой аккаунт на Авито — Александр (Александр)\n\
# Александр — это моё имя в Tinder\n\
# Александр — это как бы мой скафандр",
#     )


# @bot.message_handler(commands=["egor"])
# def reply(message):
#     bot.send_message(
#         message.chat.id,
#         f"Кати-Маши, Юли-Гали\n\
# На всякий случай тоже упали\n\
# Все попадали как забор\n\
# Остался один Егор",
#     )


@bot.message_handler(commands=["quote"])
def reply(message):
    list_w_quotes = []
    with open('quotes.txt', 'r', encoding='utf8') as file_w_quotes:
        s = file_w_quotes.readlines()
    for quote in s:
        list_w_quotes.append(quote)

    bot.send_message(message.chat.id, f"{choice(list_w_quotes)}\n\n(с) Jason Statham")


@bot.message_handler(commands=["member_list"])
def reply(message):
    # print(message.chat.id)
    if message.chat.id == '...':  # чат с друзьями Bollywood
        if message.from_user.username == "...":
            bot.send_message(message.chat.id, f"отправляю, шеф")
        bot.send_message(
            message.chat.id,
            f"Грибов Всеволод Дмитриевич 23.03.2005\n\
Дичин Александр Ильич 28.12.2004\n\
Кузнецов Арсений Эдуардович 28.11.2005\n\
Смолин Егор Максимович 21.11.2005\n\
Запрягаев Михаил Александрович 26.02.2005",
        )
    else:
        bot.send_message(message.chat.id, f"доступно только в группе")


# если после выззова poetry не ввели номер, а вызвали
# следующую команду, он забывает про poetry,
# так что отключать флаги не надо

@bot.message_handler(commands=["poetry"])  # стишок на выбранную тему
def reply(message):
    # вход в команду
    global poetry_flag
    poetry_flag = True
    with open('names_categories.txt', 'r') as file:
        m = file.read()
    bot.send_message(message.chat.id, m)  # отправляем пользователю список имён/праздников
    bot.send_message(message.chat.id, f'Могу предложить вам стихотворения по такми темам. '
                                      f'Отправьте номер выбранной темы в ответ')
    # дальше в content_types=["text"]

    # выход из команды
    # poetry_flag = False


# отключил. На постоянке она не нужна. Хочешь добавить цитат - включай, добавляй и отключай вновь
@bot.message_handler(commands=["addind_a_quote"])  # добавить цитату
def reply(message):
    # вход в команду
    global adding_a_quote_flag
    adding_a_quote_flag = True
    bot.send_message(message.chat.id, f'Какую цитату добавить в список?')
    # дальше в content_types=["text"]

    # выход из команды
    # adding_a_quote_flag = False


@bot.message_handler(commands=["call_developer"])  # написать разрабу
def reply(message):
    bot.send_message(message.chat.id, f'ник разработчика: ...\nмогу подсказать, с чего начать:\n'
                                      f'"привет, Миша! Когда выйдешь на работу?.."')


class databaseclass(object):
    @staticmethod
    def add_user(info: str, my_username: str):
        connection = sql.connect('database.db')
        cursor = connection.cursor()
        error = 'Что-то пошло не по плану...\nПожалуйста, сообщите разработчику ... об ошибке'
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

    def change_me(self, info: str, my_username: str):
        connection = sql.connect('database.db')
        cursor = connection.cursor()
        error = 'Что-то пошло не по плану...\nПожалуйста, сообщите разработчику ... об ошибке'
        # info += '\n-'
        data = [x for x in info.split('\n')]
        list_of_contacts = '-'
        try:
            cursor.execute(f'select contactslist from Users where username = "{my_username}"')
            list_of_contacts = cursor.fetchone()
            list_of_contacts = str(list_of_contacts)[2:-3]
            error = '0'
        except Exception as e:
            error = 'Вы кто такие? я вас не знаю'

        if error != '0':
            return error

        # если удалось извлечь список контактов
        data.append(list_of_contacts)
        try:
            if data[1] == my_username:
                cursor.execute(f'insert or replace into Users'
                               f'(id, username, fullname, phone, birthdate, contactslist)'
                               f'VALUES(?, ?, ?, ?, ?, ?)', (int(data[0]), data[1], data[2], data[3], data[4], data[5]))

                error = 'Изменено успешно!'
            else:
                error = 'Кажется, это не вы...'
        except Exception as e:
            print(e)
            error = 'Не удалось обновить пользователя. Пожалуйста, введите все перечисленные параметры, каждый с новой строки'

        finally:
            connection.commit()
            connection.close()
            return error


    @staticmethod
    def get_info(my_username: str, id_number: str):
        connection = sql.connect('database.db')
        cursor = connection.cursor()
        info = 'Идентификатор введён с ошибкой, или у Вас нет доступа к данным этого пользователя'
        able = False
        try:
            cursor.execute(f'select contactslist from Users where username = "{my_username}"')
            list_of_contacts = cursor.fetchone()
            list_of_contacts = str(list_of_contacts)[2:-3].split()
            if id_number in list_of_contacts:
                able = True
        except sql.Error as e:
            info = 'Вас найти не смог'

        # anyway
        finally:
            connection.commit()
        # если нет доступа
        if not able:
            connection.close()
            return info

        # если доступ есть
        try:
            cursor.execute(f'Select * from Users where id = {id_number}')
            info = cursor.fetchone()
            info = list(info)
        except sql.Error as e:
            info = 'Не удалось найти пользователя. Проверьте, правильно ли вы ввели идентификатор(id)'

        # anyway
        finally:
            connection.commit()
            connection.close()
            return info

        # обязательно в любом случае
        # connection.close()

    @staticmethod
    def print_contacts_list(message, my_username: str):
        connection = sql.connect('database.db')
        cursor = connection.cursor()
        error = 1
        try:
            cursor.execute(f'select contactslist from Users where username = "{my_username}"')
            list_of_contacts = cursor.fetchone()
            list_of_contacts = str(list_of_contacts)[2:-3].split()
            answer = ''
            for id_number in list_of_contacts:
                cursor.execute(f'select fullname from Users where id = {int(id_number)}')
                name = cursor.fetchone()
                answer += f'{id_number} {str(name)[2:-3]}' + '\n'
            bot.send_message(message.chat.id, answer)
            error = 0
        except Exception as e:
            error = 1

        finally:
            connection.commit()
            connection.close()
            return error


@bot.message_handler(commands=["add_user"])  # добавить нового пользователя
def reply(message):
    global add_user_flag
    add_user_flag = True
    bot.send_message(message.chat.id, f'Введите информацию о пользователе, каждый пункт с новой строки. '
                                      f'Если не хотите что-то указывать, напишите "-" в соответствующей строке. '
                                      f'Строки: \nИдентификатор (число)\nНикнейм\nИмя (фамилия, отчество)\n'
                                      f'Номер телефона\nДата рождения\nСписок знакомых (идентификаторы через пробел)')


@bot.message_handler(commands=["change_me"])  # добавить нового пользователя
def reply(message):
    global change_me_flag
    change_me_flag = True
    bot.send_message(message.chat.id, f'Введите обновлённую информацию, каждый пункт с новой строки. '
                                      f'Если не хотите что-то указывать, напишите "-" в соответствующей строке. '
                                      f'Строки: \nИдентификатор (число)\nНикнейм\nИмя (фамилия, отчество)\n'
                                      f'Номер телефона\nДата рождения')


@bot.message_handler(commands=["get_info"])  # вспомнить контакт
def reply(message):
    global get_info_flag
    # вход
    get_info_flag = True

    # отправляем запросившему список доступных ему контактов
    database = databaseclass()
    exit_code = database.print_contacts_list(message, str(message.from_user.username))
    if exit_code == 1:
        bot.send_message(message.chat.id, f'Не удалось высвесит список ваших контактов. '
                                          f'Пожалуйста, сообщите разработчику ... об ошибке')
    else:
        bot.send_message(message.chat.id, f'Выберите Идентификатор пользователя, данные которого хотите вспомнить')


@bot.message_handler(commands=["contacts_list"])  # список контактов
def reply(message):
    database = databaseclass()
    exit_code = database.print_contacts_list(message, str(message.from_user.username))
    if exit_code == 1:
        bot.send_message(message.chat.id, f'Не удалось высвести список ваших контактов. '
                                          f'Пожалуйста, сообщите разработчику ... об ошибке')



@bot.message_handler(content_types=["text"])
def reply(message):
    message_text = str(message.text)
    global poetry_flag, adding_a_quote_flag, get_info_flag, add_user_flag, change_me_flag
    if False:
        pass

    elif poetry_flag:  # command == ["poetry"]
        if '1' <= message_text <= '271':  # valid number?
            i = int(message_text)
            with open('links_by_names_categories.txt', 'r') as file:
                links_list = file.read().split('\n')
            link = links_list[i - 1]
            # print(type(link))
            r = requests.get(link)
            # print(r.status_code)
            soup = bs(r.content, "html.parser")
            # print(soup.a)
            poetry_list = soup.find_all(class_='sfst')
            # print(len(poetry_list))
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
        database = databaseclass()
        result = database.add_user(message.text, str(message.from_user.username))
        bot.send_message(message.chat.id, f'{result}')

        add_user_flag = False

    elif change_me_flag:
        database = databaseclass()
        result = database.change_me(message.text, str(message.from_user.username))
        bot.send_message(message.chat.id, f'{result}')

        change_me_flag = False


    elif get_info_flag:
        database = databaseclass()
        info = database.get_info(str(message.from_user.username), message.text)
        if isinstance(info, list):
            bot.send_message(message.chat.id, f'Вот что известно про этого человека:\n\n'
                                          f'Никнейм: {info[1]}\nЗовут: {info[2]}\n'
                                          f'Телефон: {info[3]}\nДата рождения: {info[4]}\n')
        else:
            bot.send_message(message.chat.id, info)

        get_info_flag = False



    elif 'Стих\n' in message_text:
        bot.send_message(message.chat.id, f"{message.from_user.first_name} Любитель Овсяных Хлопьев!")


@bot.message_handler(content_types=["voice"])
def transcript(message):
    # Функция, отправляющая текст в ответ на голосовое
    filename = download_file(bot, message.voice.file_id)
    text = recognize_speech(filename)
    bot.send_message(message.chat.id, text)


# Запускаем бота. Он будет работать, пока мы не остановим выполнение программы
bot.polling()
#bot.infinity_polling(timeout=10, long_polling_timeout = 5)
