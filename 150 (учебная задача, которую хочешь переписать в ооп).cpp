#include<algorithm>
#include<any>
#include<cassert>
#include<cmath>
#include<cstdio>
#include<deque>
#include<iostream>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<random>

#define fori(it, a, b) for(int it = a; it < b; it++)
#define all(x) (x).begin(),(x).end()
#define cn cout << '\n'
#define minel(v) *min_element(v.begin(), v.end());
#define maxel(v) *max_element(v.begin(), v.end());
#define sortv(v) sort(v.begin(), v.end());
#define forl(a, k, b) for(long long a = k; a < b; a++)
#define useless ios_base::sync_with_stdio(false); cin.tie(NULL);

using namespace std;

using ll = long long;
using str = string;
using ld = long double;
using vi = vector<int>;
using vl = vector<ll>;


struct Ship {
public:
    string name; // название судна
    pair<int, int>arrival; // день и час прибытия (по расписанию)
    int gruz_weight, gruz_type; //вес и тип груза
    int plan; // планируемое время стоянки в порту

    void addrandom(int x)
    {
        arrival.first = max(0, arrival.first + x);
    }
};


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //freopen("INPUT.TXT", "r", stdin);
    //freopen("OUTPUT.TXT", "w", stdout);



    //attention! за акждый день простоя предусмотрен штраф == 2000 дублей
    //задача: найти минимальное количество кранов, при котором общий штраф судов минимален


    //int sand = 10; //кол-во кранов для сыпучих грузов
    //int water = 15; //кол-во кранов для жидких грузов
    //int box = 20; //кол-во кранов для контейнеров


    random_device rd;   // non-deterministic generator
    mt19937 gen(rd());  // to seed mersenne twister.
    uniform_int_distribution<> distweather(0, 12); // distribute results between 1 and 6 inclusive.
    uniform_int_distribution<> distarrival(-2, 9);
    cout << distweather(gen); cn;
    cout << distarrival(gen); cn;

    unordered_map<string, int>typetime; // груз типа key разгружается value дней
    typetime["sand"] = 2;
    typetime["water"] = 4;
    typetime["box"] = 6;

    /*
    3
    Boat
    0 10
    1 20 0  
    
    Ship
    1 20
    2 10 0 

    Titanic
    2 30
    3 15 0  
    */

    setlocale(LC_ALL, "rus");

    //  --- TIMETABLE ---
    int n; //кол-во судов
    cout << "Введите...\n";
    cout << "Количество судов: \n";
    cin >> n;
    cout << "Описание судов. n раз :\n";
    cout << "-Название\n";
    cout << "*Типы грузов: 0 - сыпучий, 1 - жидкий, 2 - контейнеры\n";
    cout << "-Тип груза и вес\n";
    cout << "-день прибытия, час прибытия(1-23), планируемое время стоянки в порту(в днях)\n";
    //vector<string>name(n); // назввание суда i
    //vector<pair<int, int>>type(n); // тип груза и вес(в тоннах) (может, тип сделаешь int)
    //vector<pair<pair<int, int>, int>>time(n); // день прибытия, время прибытия (в часах), планируемое время стоянки в порту --- суда i
    vector<int>mincount(3); //min count sand
    vector<Ship>list_of_ships;
    fori(i, 0, n)
    {
        cout << "\nГруз номер " << i + 1 << '\n';
        //cin >> name[i]; 
        cin >> list_of_ships[i].name;
        //cin >> type[i].first >> type[i].second; 
        cin >> list_of_ships[i].gruz_weight;
        cin >> list_of_ships[i].gruz_type;
        //mincount[type[i].first]++;
        //cin >> time[i].first.first >> time[i].first.second >> time[i].second;
        cin >> list_of_ships[i].arrival.first;
        list_of_ships[i].addrandom(distarrival(gen));
        cin >> list_of_ships[i].arrival.second;
        cin >> list_of_ships[i].plan;
    }


    vector<int>delay;
    int c_sand = 0, c_water = 0, c_box = 0;
    fori(k, 0, 10)
    {
        //cout << '\n' << "Испытание намбер " << k + 1; cn;
        int minshtraf = 1e9;
        int cs = 0, cw = 0, cb = 0;
        fori(sand, mincount[0], 10)
        {
            fori(water, mincount[1], 10)
            {
                fori(box, mincount[2], 10)
                {
                    vector<int>waited(n);
                    int shtraf = 0;

                    // weuighttime
                    // пусть каждая тонна веса разгружается час (зависимость времени разгрузки от веса)

                    // время "из-за непогоды" (задержка по непредвиденным обстоятельствам)
                    int randomtime = distweather(gen); //0 to 12 days
                    //randomtime = 0;

                    // отклонение от планируемого времени прибытия, 
                    // от -2 до 9 дней
                    fori(i, 0, n)
                    {
                        //time[i].first.first += 0;
                        delay.push_back(distarrival(gen));
                        time[i].first.first += delay[i]; // -2 to 9 days
                        time[i].first.first = max(time[i].first.first, 0);
                    }


                    map<int, int>mp_sand; // key - когда закончит разгружаться груз value
                    map<int, int>mp_water;
                    map<int, int>mp_box;

                    //vector<map<int, int>>mp;

                    queue<pair<int, int>>q_sand; // очередь на разгрузку сыпучих
                    queue<pair<int, int>>q_water;
                    queue<pair<int, int>>q_box;

                    //vector<int>qtime(n); // сколько часов просидел в очереди

                    // моделировать по часам?
                    // пусть нового можем начать разгружать на следующий час после окончания предыдущего
                    // то есть сначала пробегаем по прибывающим судам в час h,
                    // а потом по закончившим разгрузку

                    vector<int>checked(n);

                    fori(d, 1, 30 + 1)
                    {
                        // людей из очереди закидываю на освободившиеся в прошлый час места на разгрузку
                        while (mp_sand.size() < sand)
                        {
                            if (!q_sand.empty())
                            {
                                waited[q_sand.front().second] = d - time[q_sand.front().second].first.first;
                                int end = q_sand.front().first + (waited[q_sand.front().second]) * 24;
                                mp_sand.insert({ end, q_sand.front().second });
                                q_sand.pop();
                            }
                            else
                                break;
                        }//а обслуживаются они в порядке очереди или с целью миинимизировать штраф? то есть есть смысл брать того, кто раньше закончит
                        //пусть в порядке очереди, а то иначе это неестественнно
                        while (mp_water.size() < water)
                        {
                            if (!q_water.empty())
                            {
                                waited[q_water.front().second] = d - time[q_water.front().second].first.first;
                                int end = q_water.front().first + (waited[q_water.front().second]) * 24;
                                q_water.pop();
                            }
                            else
                                break;
                        }

                        while (mp_box.size() < box)
                        {
                            if (!q_box.empty())
                            {
                                waited[q_box.front().second] = d - time[q_box.front().second].first.first;
                                int end = q_box.front().first + (waited[q_box.front().second]) * 24;
                                q_box.pop();
                            }
                            else
                                break;
                        }


                        fori(i, 0, n) // постановка на разгрузку/в очередь приходящих в день d
                        {
                            if (checked[i] > 0)
                                continue;
                            int day = list_of_ships[i].arrival.first;
                            int hour = list_of_ships[i].arrival.second;
                            int start = (day - 1) * 24 + hour;
                            if (start < (d+1)*24)
                            {
                                checked[i] = 2; //встал в очередь/на погрузку
                                int tp = list_of_ships[i].gruz_type;
                                int end = start + typetime["sand"] * list_of_ships[i].gruz_weight + 24 * randomtime;
                                //             производительность  * вес 
                                if (tp == 0)
                                {
                                    if (mp_sand.size() < sand)
                                    {
                                        mp_sand.insert({ end, i });
                                    }
                                    else {
                                        q_sand.push({ end, i });
                                    }
                                }
                                else if (tp == 1)
                                {
                                    if (mp_water.size() < water)
                                    {
                                        mp_water.insert({ end, i });
                                    }
                                    else {
                                        q_water.push({ end, i });
                                    }
                                }
                                else if (tp == 2)
                                {
                                    if (mp_box.size() < box)
                                    {
                                        mp_box.insert({ end, i });
                                    }
                                    else {
                                        q_box.push({ end, i });
                                    }
                                }
                            }
                        }

                        // проводы закончивших разгрузку в день d
                        while (mp_sand.size() && mp_sand.begin()->first < (d + 1) * 24)
                        {
                            int nomer = mp_sand.begin()->second;
                            int konec = mp_sand.begin()->first / 24 + (mp_sand.begin()->first % 24 != 0);
                            if (konec - (time[nomer].first.first + time[nomer].second) > 0)
                                shtraf += konec - (time[nomer].first.first + time[nomer].second);
                            mp_sand.erase(mp_sand.begin());
                            checked[nomer] = 1;
                            /*cn;  cout << name[nomer] << '\n';
                            cout << "Пришёл в\n";
                            cout << time[nomer].first.first << ' ' << time[nomer].first.second; cn;
                            cout << "Ждал " << waited[nomer]; cn;
                            cout << "Начали " << time[nomer].first.first + waited[nomer]; cn;
                            cout << "Разгружали " << konec - (time[nomer].first.first + waited[nomer]); cn;*/
                        }

                        while (mp_water.size() && mp_water.begin()->first < (d + 1) * 24)
                        {
                            int nomer = mp_water.begin()->second;
                            int konec = mp_water.begin()->first / 24 + (mp_water.begin()->first % 24 != 0);
                            if (konec - (time[nomer].first.first + time[nomer].second) > 0)
                                shtraf += konec - (time[nomer].first.first + time[nomer].second);
                            mp_water.erase(mp_water.begin());
                            checked[nomer] = 1;
                            /*cn; cout << name[nomer] << '\n';
                            cout << "Пришёл в\n";
                            cout << time[nomer].first.first << ' ' << time[nomer].first.second; cn;
                            cout << "Ждал " << waited[nomer]; cn;
                            cout << "Начали " << time[nomer].first.first + waited[nomer]; cn;
                            cout << "Разгружали " << konec - (time[nomer].first.first + waited[nomer]); cn;*/
                        }

                        while (mp_box.size() && mp_box.begin()->first < (d + 1) * 24)
                        {
                            int nomer = mp_box.begin()->second;
                            int konec = mp_box.begin()->first / 24 + (mp_box.begin()->first % 24 != 0);
                            if (konec - (time[nomer].first.first + time[nomer].second) > 0)
                                shtraf += konec - (time[nomer].first.first + time[nomer].second);
                            mp_box.erase(mp_box.begin());
                            checked[nomer] = 1;
                            /*cn; cout << name[nomer] << '\n';
                            cout << "Пришёл в\n";
                            cout << time[nomer].first.first << ' ' << time[nomer].first.second; cn;
                            cout << "Ждал " << waited[nomer]; cn;
                            cout << "Начали " << time[nomer].first.first + waited[nomer]; cn;
                            cout << "Разгружали " << konec - (time[nomer].first.first + waited[nomer]); cn;*/
                        }

                    }
                    fori(i, 0, n)
                    {
                        if (checked[i] != 1)
                            shtraf += 30;
                    }
                    if (shtraf < minshtraf) //штраф считаю в днях, потому что пока не нужен в тугриках
                    {
                        minshtraf = shtraf;
                        cs = sand;
                        cw = water;
                        cb = box;
                    }
                }
            }
        }
        
        c_sand += cs;
        c_water += cw;
        c_box += cb;
    }

    c_sand /= 10;
    c_water /= 10;
    c_box /= 10;
    vector<int>waited(n);
    int shtraf = 0;

    //МОДЕЛИРОВАНИЕ ЛУЧШЕГО РЕЗУЛЬТАТА



    // weuighttime
    // пусть каждая тонна веса разгружается час (зависимость времени разгрузки от веса)

    // время "из-за непогоды" (задержка по непредвиденным обстоятельствам)
    int randomtime = distweather(gen); //0 to 12 days
    //randomtime = 0;

    //vector<int>delay; 
    // отклонение от планируемого времени прибытия, 
    // от -2 до 9 дней
    fori(i, 0, n)
    {
        time[i].first.first += 0;
        time[i].first.first += distarrival(gen); // -2 to 9 days
        time[i].first.first = max(time[i].first.first, 0);
    }


    map<int, int>mp_sand; // key - когда закончит разгружаться груз value
    map<int, int>mp_water;
    map<int, int>mp_box;

    //vector<map<int, int>>mp;

    queue<pair<int, int>>q_sand; // очередь на разгрузку сыпучих
    queue<pair<int, int>>q_water;
    queue<pair<int, int>>q_box;

    //vector<int>qtime(n); // сколько часов просидел в очереди

    // моделировать по часам?
    // пусть нового можем начать разгружать на следующий час после окончания предыдущего
    // то есть сначала пробегаем по прибывающим судам в час h,
    // а потом по закончившим разгрузку

    vector<int>checked(n);
    int sand = c_sand;
    int water = c_water;
    int box = c_box;
    cout << "\nПРОЦЕСС...\n";
    
    fori(d, 1, 30 + 1)
    {
        // людей из очереди закидываю на освободившиеся в прошлый час места на разгрузку
        while (mp_sand.size() < sand)
        {
            if (!q_sand.empty())
            {
                waited[q_sand.front().second] = d - time[q_sand.front().second].first.first;
                int end = q_sand.front().first + (waited[q_sand.front().second]) * 24;
                mp_sand.insert({ end, q_sand.front().second });
                q_sand.pop();
            }
            else
                break;
        }//а обслуживаются они в порядке очереди или с целью миинимизировать штраф? то есть есть смысл брать того, кто раньше закончит
        //пусть в порядке очереди, а то иначе это неестественнно
        while (mp_water.size() < water)
        {
            if (!q_water.empty())
            {
                waited[q_water.front().second] = d - time[q_water.front().second].first.first;
                int end = q_water.front().first + (waited[q_water.front().second]) * 24;
                q_water.pop();
            }
            else
                break;
        }

        while (mp_box.size() < box)
        {
            if (!q_box.empty())
            {
                waited[q_box.front().second] = d - time[q_box.front().second].first.first;
                int end = q_box.front().first + (waited[q_box.front().second]) * 24;
                q_box.pop();
            }
            else
                break;
        }


        fori(i, 0, n) // постановка на разгрузку/в очередь приходящих в день d
        {
            if (checked[i] > 0)
                continue;
            int day = time[i].first.first;
            int hour = time[i].first.second;
            int start = (day - 1) * 24 + hour + delay[i] * 24;
            if (start < (d + 1) * 24)
            {
                checked[i] = 2; //встал в очередь/на погрузку
                int tp = type[i].first;
                int end = start + typetime["sand"] * type[i].second + 24 * randomtime;
                //             производительность  * вес 
                if (tp == 0)
                {
                    if (mp_sand.size() < sand)
                    {
                        mp_sand.insert({ end, i });
                    }
                    else {
                        q_sand.push({ end, i });
                    }
                }
                else if (tp == 1)
                {
                    if (mp_water.size() < water)
                    {
                        mp_water.insert({ end, i });
                    }
                    else {
                        q_water.push({ end, i });
                    }
                }
                else if (tp == 2)
                {
                    if (mp_box.size() < box)
                    {
                        mp_box.insert({ end, i });
                    }
                    else {
                        q_box.push({ end, i });
                    }
                }
            }
        }

        // проводы закончивших разгрузку в день d
        while (mp_sand.size() && mp_sand.begin()->first < (d + 1) * 24)
        {
            int nomer = mp_sand.begin()->second;
            int konec = mp_sand.begin()->first / 24 + (mp_sand.begin()->first % 24 != 0);
            if (konec - (time[nomer].first.first + time[nomer].second) > 0)
                shtraf += konec - (time[nomer].first.first + time[nomer].second);
            mp_sand.erase(mp_sand.begin());
            checked[nomer] = 1;
            cn;  cout << name[nomer] << '\n';
            cout << "Пришёл в день, час\n";
            cout << time[nomer].first.first << ' ' << time[nomer].first.second; cn;
            cout << "Ждал дней " << waited[nomer]; cn;
            cout << "Начали в день " << time[nomer].first.first + waited[nomer]; cn;
            cout << "Разгружали дней " << konec - (time[nomer].first.first + waited[nomer]); cn;
        }

        while (mp_water.size() && mp_water.begin()->first < (d + 1) * 24)
        {
            int nomer = mp_water.begin()->second;
            int konec = mp_water.begin()->first / 24 + (mp_water.begin()->first % 24 != 0);
            if (konec - (time[nomer].first.first + time[nomer].second) > 0)
                shtraf += konec - (time[nomer].first.first + time[nomer].second);
            mp_water.erase(mp_water.begin());
            checked[nomer] = 1;
            cn; cout << name[nomer] << '\n';
            cout << "Пришёл в день, час\n";
            cout << time[nomer].first.first << ' ' << time[nomer].first.second; cn;
            cout << "Ждал дней " << waited[nomer]; cn;
            cout << "Начали в день " << time[nomer].first.first + waited[nomer]; cn;
            cout << "Разгружали дней " << konec - (time[nomer].first.first + waited[nomer]); cn;
        }

        while (mp_box.size() && mp_box.begin()->first < (d + 1) * 24)
        {
            int nomer = mp_box.begin()->second;
            int konec = mp_box.begin()->first / 24 + (mp_box.begin()->first % 24 != 0);
            if (konec - (time[nomer].first.first + time[nomer].second) > 0)
                shtraf += konec - (time[nomer].first.first + time[nomer].second);
            mp_box.erase(mp_box.begin());
            checked[nomer] = 1;
            cn; cout << name[nomer] << '\n';
            cout << "Пришёл в день, час\n";
            cout << time[nomer].first.first << ' ' << time[nomer].first.second; cn;
            cout << "Ждал дней " << waited[nomer]; cn;
            cout << "Начали в день " << time[nomer].first.first + waited[nomer]; cn;
            cout << "Разгружали дней " << konec - (time[nomer].first.first + waited[nomer]); cn;
        }

    }
    

    cout << "\n\n" << "ИИИИИтог моделирования... Надо:\n";
    cout << "Кранов для сыпучих " << c_sand << '\n';
    cout << "Кранов для жидких " << c_water << '\n';
    cout << "Кранов для контейнеров " << c_box << '\n';
}

