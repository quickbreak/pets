import os
import telebot
import speech_recognition
from pydub import AudioSegment
from PIL import Image, ImageEnhance, ImageFilter
from random import *
import sqlite3 as sql
from bs4 import BeautifulSoup as bs
import requests

# ↓ Токен, который дал BotFather при регистрации
token = ""  # <<< Ваш токен

bot = telebot.TeleBot(token)

adding_a_quote_flag = False
poetry_flag = False
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

    if message.chat.id == 123:  # мой аккаунт
        bot.send_message(message.chat.id, f"добрый день")
    elif message.from_user.first_name == "Миша":
        bot.send_message(message.chat.id, f"добрый день, master")
    else:
        bot.send_message(
            message.chat.id, f"{message.from_user.first_name} banned. Say bye to him"
        )
    # New Year edition
    # if message.from_user.first_name == "Миша":
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
    if message.chat.id == 123:  # мой аккаунт
        bot.send_message(message.chat.id, f"здрасьте, шеф")

    if message.chat.id == 123:  # чат с друзьями Bollywood
        if message.from_user.first_name == "Миша":
            bot.send_message(message.chat.id, f"отправляю, шеф")
        bot.send_message(
            message.chat.id,
            f"",
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


@bot.message_handler(content_types=["text"])
def reply(message):
    message_text = str(message.text)
    global poetry_flag, adding_a_quote_flag
    if 'dfvs dvs' in message_text:
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

# with open('quotes.txt', 'r', encoding="utf8") as f:
#     a = f.read()
#     print(a)
