# This is the way
# pythontoday
# YouTube: https://www.youtube.com/c/PythonToday/videos

import re
from bs4 import BeautifulSoup as bs
import requests


def biglist():
    print('Большой список')
    r = requests.get(
        "https://priem.mirea.ru/accepted-entrants-list/personal_code_rating.php?competition=1748205422769085750")
    soup = bs(r.content, 'html.parser')
    print(f'{soup.find(class_="lastUpdate").text[20:]}:')
    people = soup.find(class_="namesTable")
    people = people.text.split('\n')
    flag = False
    print('* ', end='')
    for item in people:
        if "157-074-618-76" in item:
            flag = True
            print('в таблице есть')
            print('* ', end='')
            print(f'номер {item[3:6]} из 156')
            print('* ', end='')
        elif flag:
            if "Преим. право" in item:
                print('win, Преим. право')
            else:
                print('На общих основаниях')
            break
    if flag == 0:
        print('В списке даже нет :(')


def withoutexams():
    print('Список поступающих без экзаменов')
    r = requests.get(
        "https://priem.mirea.ru/accepted-entrants-list/personal_code_rating.php?competition=1748205422768037174")
    soup = bs(r.content, 'html.parser')
    print(f'{soup.find(class_="lastUpdate").text[20:]}:')
    people = soup.find(class_="namesTable")
    people = people.text.split('\n')
    flag = False
    print('* ', end='')
    #print(people)
    for item in people:
        if "157-074-618-76" in item:
            print('в таблице есть')
            print('* ', end='')
            ind = item.index("157-074-618-76")
            print(f'номер {item[ind-2:ind]} из 156')
            print('* ', end='')
            flag = True
            break
    if flag == 0:
        print('В таблице даже нет :(')


def itmo():
    print('ITMO?')
    r = requests.get("https://abitlk.itmo.ru/personal/documents")
    soup = bs(r.content, 'html.parser')
    print(soup)
    print(soup.find(class_="PersonalDocumentsForm_paragraph__first__lEX44"))


def easyaka():
    for i in range(5):
        r = requests.get(f'https://stopgame.ru/news/all/p{i + 1}')
        soup = bs(r.content, 'html.parser')
        titles = soup.find_all(class_="_title_1tbpr_49")
        for x in titles:
            print(x.text)


def iphone():
    print("курс доллара по версии центрального банка России:")
    r = requests.get("https://cbr.ru/")
    print(r)
    soup = bs(r.content, 'html.parser')
    # print(soup.text)
    #exit()
    b = soup.find(class_="main-indicator_rates-head").find_all(class_="col-md-2 col-xs-7 _right")
    print(b[0].text, b[1].text, sep="         ")
    a = [x.find_all(class_="col-md-2 col-xs-9 _right mono-num") for x in soup.find_all(class_="main-indicator_rate")]
    print(a[1][0].text.replace("\r\n\t\t\t\t\t\t", ""), a[1][1].text.replace("\r\n\t\t\t\t\t\t", ""), sep="          ")
    print("\nцены на biggeek:")
    #16.07.2023:
    #12 - 56990
    #13 - 66990
    #14 - 75990
    for c in range(2, 4 + 1):
        r = requests.get(f"https://biggeek.ru/catalog/apple-iphone-1{c}")
        soup = bs(r.content, 'html.parser')
        wishlist = soup.find_all(class_="catalog-card")
        a = []
        for item in wishlist:
            a.append(int(item.find(class_="cart-modal-count").text.replace("₽", "").replace(" ", "").replace("от", "")))
        a.sort()
        print(f"iPhone 1{c}")
        print(a)


#biglist()
#withoutexams()
# itmo()
#easyaka()
iphone()

# title = soup.title
# print(title)
# print(title.text)
# print(title.string)

# .find() .find_all()
# page_h1 = soup.find("h1")
# print(page_h1)
#
# page_all_h1 = soup.find_all("h1")
# print(page_all_h1)
#
# for item in page_all_h1:
#     print(item.text)

# user_name = soup.find("div", class_="user__name")
# print(user_name.text.strip())

# user_name = soup.find(class_="user__name").find("span").text
# print(user_name)

# user_name = soup.find("div", {"class": "user__name", "id": "aaa"}).find("span").text
# print(user_name)

# find_all_spans_in_user_info = soup.find(class_="user__info").find_all("span")
# print(find_all_spans_in_user_info)

# for item in find_all_spans_in_user_info:
#     print(item.text)

# print(find_all_spans_in_user_info[0])
# print(find_all_spans_in_user_info[2].text)

# social_links = soup.find(class_="social__networks").find("ul").find_all("a")
# print(social_links)

# all_a = soup.find_all("a")
# print(all_a)
#
# for item in all_a:
#     item_text = item.text
#     item_url = item.get("href")
#     print(f"{item_text}: {item_url}")

# .find_parent() .find_parents()

# post_div = soup.find(class_="post__text").find_parent()
# print(post_div)

# post_div = soup.find(class_="post__text").find_parent("div", "user__post")
# print(post_div)

# post_divs = soup.find(class_="post__text").find_parents("div", "user__post")
# print(post_divs)

# .next_element .previous_element
# next_el = soup.find(class_="post__title").next_element.next_element.text
# print(next_el)
#
# next_el = soup.find(class_="post__title").find_next().text
# print(next_el)

# .find_next_sibling() .find_previous_sibling()
# next_sib = soup.find(class_="post__title").find_next_sibling()
# print(next_sib)

# prev_sib = soup.find(class_="post__date").find_previous_sibling()
# print(prev_sib)

# post_title = soup.find(class_="post__date").find_previous_sibling().find_next().text
# print(post_title)

# links = soup.find(class_="some__links").find_all("a")
# print(links)
#
# for link in links:
#     link_href_attr = link.get("href")
#     link_href_attr1 = link["href"]
#
#     link_data_attr = link.get("data-attr")
#     link_data_attr1 = link["data-attr"]
#
#     print(link_href_attr1)
#     print(link_data_attr1)

# find_a_by_text = soup.find("a", text="Одежда")
# print(find_a_by_text)
#
# find_a_by_text = soup.find("a", text="Одежда для взрослых")
# print(find_a_by_text)

# find_a_by_text = soup.find("a", text=re.compile("Одежда"))
# print(find_a_by_text)

# find_all_clothes = soup.find_all(text=re.compile("([Оо]дежда)"))
# print(find_all_clothes)
