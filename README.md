# snake
c++ ncurses 라이브러리를 이용한 Snake game 구현

Snake game implemented using c++ ncurses library

# Description
 ![image](https://github.com/soominyeo/snake/assets/40330524/59b27f81-c47e-4442-a6f7-e28ab15358da)
 
  Run.sh 스크립트를 실행하면 자신의 이름을 입력하라는 메세지가 출력되며, 이름을 입력하고 엔터를 입력하면 바로 게임이 시작된다.
  
![image](https://github.com/soominyeo/snake/assets/40330524/af8a5d64-0f23-4fef-9a57-6782963c4b4c)

 게임을 시작하면 위와 같은 모습의 화면이 출력된다. 화면 상에서 움직이는 ###%가 snake에 해당하며, 1과 2, 3이 벽, A나 B, S, M가 각각 Apple, Bomb, Strawberry, Melon 아이템이고, $가 게이트이다. Wasd 키를 이용하여 snake의 방향을 변경할 수 있으며, snake는 일정 시간마다 보고 있는 방향으로 움직이며, 벽 등의 장애물과 만나거나 길이가 3보다 작아지면 게임이 종료된다.
 
각 아이템은 다음과 같이 각기 다른 효과를 가지고 있는데, 해당 스테이지를 클리어하기 위해서는 각각 일정 개수 이상을 획득할 필요가 있다.
-	Apple 아이템을 먹으면 snake의 길이가 한 칸 늘어난다.
-	Bomb 아이템을 먹으면 snake의 길이가 한 칸 줄어든다.
-	Strawberry 아이템을 먹으면 snake가 자동으로 움직이는 속도가 빨라진다.
-	Melon 아이템을 먹으면 부술 수 있는 벽(3으로 표시됨)을 한 번에 한해 부수고 통과할 수 있다.

![image](https://github.com/soominyeo/snake/assets/40330524/28457e19-ff22-49cf-bb99-8806b77b33b6)

 게임 오버가 되면 자기 자신의 점수와 함께 전에 플레이했던 사람들의 기록 및 순위가 출력된다.  이후 게임을 종료하려면 q, 게임을 다시 플레이하려면 그 외 아무 키를 입력하면 된다.

 
# Build
해당 프로그램을 컴파일하기 위해서는 선행 조건으로 make, gcc, ncurses 라이브러리가 설치되어 있어야 한다.

```bash
~$ git clone https://github.com/soominyeo/snake.git
```
위 조건을 만족한다면 해당 프로젝트의 소스 코드를 git clone 등의 방법으로 로컬에 다운로드한다.

```bash
~$ cd snake
~/snake$ make
g++ -c src/snake.cpp -o obj/snake.o -Wall -I/usr/include/ncurses
g++ -c src/leaderboard.cpp -o obj/leaderboard.o -Wall -I/usr/include/ncurses
g++ -c src/snake_game.cpp -o obj/snake_game.o -Wall -I/usr/include/ncurses
...
```
이후 다운로드한 소스의 최상단 디렉토리에서 터미널을 통해 make 명령어를 입력하면 빌드가 진행되고, 실행파일 main이 build/ 이하 디렉토리에 생성된다.

```bash
~/snake$ ./build/main
or
~/snake$ ./run.sh
```
이 main을 직접 실행해도 되지만 소스 코드에 동봉된 run.sh bash 스크립트를 이용하면 터미널의 크기를 최적의 크기로 조정한 이후 실행할 수 있다.



# Demo
https://youtu.be/sjidQMEU5Qk
&nbsp;

# Notion
https://confirmed-mustang-854.notion.site/f1b328be65694eeea579bdc70e9d3698?pvs=4
&nbsp;
