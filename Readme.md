**Игровой движок на C++ с помощью графического API OpenGL**

Игровой движок для создания простого top down шутера.

В этом проекте также реализована небольшая игра: выживание на арене против орд зомби.
Нет ограничений, бесконечные волны, в целом "весело".

Скриншоты из игры:

![скриншот проекта](https://github.com/xomageimer/GameEngineOpenGL/blob/master/doc/gitsimage/start.PNG)

![скриншот проекта](https://github.com/xomageimer/GameEngineOpenGL/blob/master/doc/gitsimage/death1.PNG)

![скриншот проекта](https://github.com/xomageimer/GameEngineOpenGL/blob/master/doc/gitsimage/z.PNG)

![скриншот проекта](https://github.com/xomageimer/GameEngineOpenGL/blob/master/doc/gitsimage/zombies.PNG)

![скриншот проекта](https://github.com/xomageimer/GameEngineOpenGL/blob/master/doc/gitsimage/zombiesblood.PNG)

Вывод в коносль в случае смерти:

![скриншот проекта](https://github.com/xomageimer/GameEngineOpenGL/blob/master/doc/gitsimage/died.PNG)

Попробовать игру под windows (в игре отсутсвуют скримеры, всё что может вас напугать - баги и лаги, извиняюсь за них):

https://drive.google.com/drive/folders/1s_N0RC9oZ9tY7fI0m-pDIP1mAR0YPHvR?usp=sharing


#Идеи на следующий движок по архитектуре:
    ** Необходимо создать структуру Timer для обработки всех временых счетчиков (время между кадрами, между смертью моба и его воскрешением, между смертью игрока и рестартом игры)**
    ** Имплеменитровать это всё в Engine и сделать какой-нибудь observer, кт будет решать когда и что нужно отобразить с учетом времени (интерфейс стоит продумать какой-нибудь уникальный и единичный, работающий для всех разных объектов) **
    ** Подумать о том как можно улучшить архитектуру метода Update для калссов пространства Actor **
