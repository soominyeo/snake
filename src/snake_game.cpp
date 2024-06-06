#include <chrono>
#include "snake_game.hpp"

namespace snake{
    // 생성자 호출 시 게임 창을 stage 0번으로 초기화
    SnakeGame::SnakeGame(int stageNum)
    {
        initialize(stageNum);
    }

    // 소멸자 호출 시 동적으로 할당했던 변수 delete
    SnakeGame::~SnakeGame()
    {
        delete apple;
        delete bomb;
        delete warp1;
        delete warp2;
        delete melon;
        delete strawberry;
    }

    // 게임 시작할 시(= 생성자 호출 될 시) 진행하는 로직
    void SnakeGame::initialize(int stageNum)
    {   
        bool bonusTrigger = false;

        if (stageNum >= 4)
        {
            stageNum = 4;
            bonusTrigger = true;
        }
        
        // 게임 창을 stageNum 번째 stage로 초기화
        board.initialize(stageNum);

        // bonus stage는 벽이 랜덤으로 생성됨
        if (bonusTrigger == true)
        {
            for (int i = 0; i < 20; i++)
            {
                int y, x;
                board.getBonusWallPos(y, x);
                board.add(y, x, '3');
            }
        }

        // missionboard 
        missionboard.init();

        // 초기화될 때마다 rand 시드 바꾼다
        srand(time(NULL));

        // snake queue를 게임 창 좌측 상단에 ###@ 형태로 초기화
        snake.initialize();

        // 게임 창에 메모리 상으로 초기화 된 snake 위치 표시한다
        board.add(1, 4, '%');
        board.add(1, 3, '#');
        board.add(1, 2, '#');
        board.add(1, 1, '#');

        // 사과랑 폭탄 만든다
        createApple();
        createBomb();
        createWarp();
        createStrawberry();
        if(board.getStageNum()!=0){
            createMelon();
            for(int i=0; i<3; i++)
                createDWall();
            deleteItem();
        }
        tick_count1=10;
        tick_count2=10;
        power=0;
        // 게임 초기화시 다시 카운터 해야하는 변수 초기화
        apple_counter=0;
        bomb_counter=0;
        warp_counter=0;
        strawberry_counter=0;
        melon_counter=0;   
        }

    // 사과 만드는 함수
    void SnakeGame::createApple()
    {
        int y, x;

        // 아이템이 생성될 수 있는 위치 get하기
        board.getItemPos(y, x);

        apple = new Apple(y, x);

        // 게임 창의 메모리 상으로 사과 A 추가
        board.add(y, x, 'A');
    }

    // 폭탄 만드는 함수
    void SnakeGame::createBomb()
    {
        int y, x;

        // 아이템이 생성될 수 있는 위치 get하기
        board.getItemPos(y, x);

        bomb = new Bomb(y, x);

        // 게임 창의 메모리 상으로 사과 B 추가
        board.add(y, x, 'B');
    }

    void SnakeGame::createWarp()
    {
        int y, x;
        board. getWarpPos(y,x);
        warp1=new Warp(y,x);
        board.add(y, x, '$');

        board. getWarpPos(y,x);
        warp2=new Warp(y,x);
        board.add(y, x, '$');
    }

    // 딸기(= speedUP) 만드는 함수
    void SnakeGame::createStrawberry()
    {
        int y, x;

        // 아이템이 생성될 수 있는 위치 get하기
        board.getItemPos(y, x);

        strawberry = new Strawberry(y, x);

        // 게임 창의 메모리 상으로 딸기 추가
        board.add(y, x, 'S');
    }
    void SnakeGame::createMelon()
    {
        int y, x;
        board.getItemPos(y, x);
        melon = new Melon(y, x);
        board.add(y, x, 'M');
    }

    void SnakeGame::createDWall()
    {
        int y, x;
        board.getDWallPos(y, x);
        board.add(y, x, '3');  
    }

    // 입력 받은 값에 따라 작동을 달리하는 로직
    void SnakeGame::getInputState()
    {
        char input = board.getInput();

        switch (input)
        {
            // w a s d로 뱀 움직이기
            // setDirection(direction)은 현재 방향과 반대 방향 키를 누르면 false 반환, 아니면 true 반환한다
            // 반대 방향 키를 누르면 게임 오버가 되도록 설정
            case 'w':
            case 'W':
                if (!snake.setDirection(up))
                    game_over = true;
                break;
            case 's':
            case 'S':
                if (!snake.setDirection(down))
                    game_over = true;
                break;
            case 'd':
            case 'D':
                if (!snake.setDirection(right))
                    game_over = true;
                break;
            case 'a':
            case 'A':
                if (!snake.setDirection(left))
                    game_over = true;
                break;

            // p 누르면 pause
            case 'p':
            case 'P':
                // 게임 창 속도를 음수로 함으로써 멈추게 한다
                board.setTimeout(-1);
                // p가 다시 입력될 때까지 while문 못 빠져 나감
                while (board.getInput() != 'p')
                    ;
                // while문 빠져 나왔다는 것은 p를 다시 눌렀다는 것이니까
                // 다시 게임 속도 원상태로 돌려놓기
                board.setTimeout(300);
                break;
            
            // 임시로 만든 기능. n 누르면 다음 스테이지로 넘어감
            case 'n':
            case 'N':
                // 현재 게임의 stage 번호를 num에 저장
                int num = getStageNum();

                // 다음 스테이지로 넘어가야하므로 ++num 한 것
                initialize(++num);
                break;
        }
    }

    // 게임을 플레이하는 동안 진행하는 로직
    void SnakeGame::playingState()
    {
        missionboard.drawScore(calculate_score(5));
        
        // next는 snake가 다음 어디로 가야할지 그 위치의 값을 가진 SnakePiece이다
        SnakePiece next = snake.nexthead();

        if(board.getCharAt(next.getY(), next.getX())== '$')
        {
            warp_counter++;
            calculate_score(2);
            missionboard.drawGateway_mission(get_warp_Counter());

            tick_count1=0;
            if((next.getY()==warp1->getY()) && (next.getX()==warp1->getX())){
                //check 4 direction of warp2
                //UP, DOWN, RIGHT, LEFT
                checkWarp(next, warp2);
            }
            else if((next.getY()==warp2->getY()) && (next.getX()==warp2->getX())){
                checkWarp(next, warp1);
            }
            handleNext(next);
        }
        else
            // next 라는 SnakePiece를 가지고 뱀을 조종
            handleNext(next);

        if(warp1!=NULL && warp2!=NULL)
        {
            tick_count1++;
        }

        if(melon!=NULL)
        {
            tick_count2++;
        }

        if(tick_count1==snake.getSize()+2)
        {
            endWarp();
        }

        if(tick_count2==snake.getSize()+2)
        {
            board.add(DWall_y,DWall_x, '1');
        }
    
        // 만약 사과나 폭탄이 NULL 상태라면 생성해야 한다
        if (apple == NULL)
        {
            createApple();
        }

        if (bomb == NULL)
        {
            createBomb();
        }

        if(warp1==NULL && warp2==NULL)
        {
            createWarp();
        }

        if (strawberry == NULL)
        {
            createStrawberry();
        }

        // 만약 snake의 몸 길이가 3 미만이라면 게임 오버로 간주
        if (snake.getSize() < 3)
        {
            game_over = true;
        }
        if(melon ==NULL && board.getStageNum() != 0)
        {
            createMelon();
        }
        
        // 만약 미션 목표를 달성했으면 다음 스테이지로 
        if((get_apple_Counter()>=5)&&(get_bomb_Counter()>=5)&&(get_warp_Counter()>=5)&&(snake.getSize()>=5)&&(get_strawberry_Counter()>=5))
        {
            int num = getStageNum();

            // 스테이지 0에서는 melon을 안 먹으므로 melon은 반영하면 안된다
            if (num == 0)
                initialize(++num);
            else
                if (get_melon_Counter() >= 5)
                    initialize(++num);
        }
    }

    // 뱀이 다음 위치로 어떻게 나아가야하는지 icon에 따라 조종하는 함수
    void SnakeGame::handleNext(SnakePiece& next)
    {   
        int nextRow = next.getY();
        int nextCol = next.getX();

        // 미션 보드에 현재 몸길이 출력
        missionboard.drawCurrent_mission(snake.getSize()); 

        // 만약 다음으로 나아갈 위치가 ' '이라면
        // 이하 "뱀이 앞으로 나아가는 로직" 이라고 칭함
        if (board.getCharAt(nextRow, nextCol) == ' ' || (board.getCharAt(nextRow, nextCol) == 'M') ||((melon!=NULL) && (power!=0) && (board.getCharAt(nextRow, nextCol) == '3')))
        {   
            if((melon!=NULL) && (power!=0) && (board.getCharAt(nextRow, nextCol) == '3'))
            {
                DWall_y=nextRow, DWall_x=nextCol;
                tick_count2=0;
                createDWall();
                power--;

                // '3'을 부술 때마다 melon 먹은거 하나 없어짐
                melon_counter--;
                missionboard.drawMelon_mission(get_melon_Counter());
            }
            if(board.getCharAt(nextRow, nextCol) == 'M')
            {   
                melon_counter++;
                calculate_score(4);
                missionboard.drawMelon_mission(get_melon_Counter()); 
                power++;

                // 먹자마자 melon NULL로 한다
                board.add(nextRow, nextCol, ' ');
                //delete melon
                delete melon;
                melon=NULL;
            }

            // snake의 꼬리 위치에다가 ' ' add 한다
            board.add(snake.tail().getY(), snake.tail().getX(), ' ');
            // snake의 꼬리를 없앤다
            snake.removeBody();

            // 현 상태의 snake의 머리 부분의 icon을 '#'으로 설정
            snake.head().setIcon('#');
            // 게임 창에도 똑같이 snake의 머리 부분 위치를 '#'으로 바꿈(=add)
            board.add(snake.head().getY(), snake.head().getX(), '#');

            // snake에다가 next 추가
            snake.addBody(next);
            // next를 추가한 최종 snake의 머리 부분의 icon을 '@'로 설정
            snake.head().setIcon('%');
            // 게임 창에도 똑같이 반영
            board.add(snake.head().getY(), snake.head().getX(), '%');
        }

        // 사과를 먹는다면
        else if (board.getCharAt(nextRow, nextCol) == 'A')
        {
            // 미션 보드에 Apple 먹은 횟수 업데이트
            apple_counter++;
            calculate_score(0);
            missionboard.drawApple_mission(get_apple_Counter()); 
            // 사과 먹는 함수 실행
            eatApple();

            // 뱀이 앞으로 나아가는 로직에서 꼬리 부분을 없애는 과정을 건너뛰면 된다
            snake.head().setIcon('#');
            board.add(snake.head().getY(), snake.head().getX(), '#');

            snake.addBody(next);
            snake.head().setIcon('%');
            board.add(snake.head().getY(), snake.head().getX(), '%');
        }

        // 폭탄을 먹는다면
        else if (board.getCharAt(nextRow, nextCol) == 'B')
        {  

            // 미션 보드에 Bomb 먹은 횟수 업데이트
            bomb_counter++; // 먹으면 bomb(itemp.hpp)카운터 증가
            calculate_score(1);
            missionboard.drawBomb_mission(get_bomb_Counter()); 

            // 폭탄을 먹는 함수 실행
            eatBomb();
            
            // 꼬리를 한번 더 삭제하고 앞으로 나아가는 로직 진행
            board.add(snake.tail().getY(), snake.tail().getX(), ' ');
            snake.removeBody();

            board.add(snake.tail().getY(), snake.tail().getX(), ' ');
            snake.removeBody();

            snake.head().setIcon('#');
            board.add(snake.head().getY(), snake.head().getX(), '#');

            snake.addBody(next);
            snake.head().setIcon('%');
            board.add(snake.head().getY(), snake.head().getX(), '%');
        }

        else if (board.getCharAt(nextRow, nextCol) == 'S')
        {
             // 미션 보드에 Strawberry 먹은 횟수 업데이트
            strawberry_counter++; // 먹으면 strawberry(itemp.hpp)카운터 증가
            calculate_score(3);
            missionboard.drawStrawberry_mission(get_strawberry_Counter());

            // 딸기 먹는 함수 실행
            eatStrawberry();

            int tick = board.getSpeedTick();

            if (tick > 50)
            {
                tick -= 50;
            }
            
            board.setTimeout(tick);
        }
        // Wall(= '1')을 만났을 때, 뱀 몸통(=자기 자신)을 만났을 때
        else
        {
            game_over = true;
        }
    }

    // 사과를 없애는(=먹는) 함수
    void SnakeGame::eatApple()
    {   
        
        // 우선 보드에 기존의 사과 위치에다가 ' ' add한다
        board.add(apple->getY(), apple->getX(), ' ');
        
        // 동적할당 했었던 apple 없애고 apple을 NULL로 하자
        delete apple;
        apple = NULL;
    }

    // 폭탄를 없애는(=먹는) 함수
    void SnakeGame::eatBomb()
    {   
        // 우선 보드에 기존의 폭탄 위치에다가 ' ' add한다
        board.add(bomb->getY(), bomb->getX(), ' ');

        // 동적할당 했었던 bomb 없애고 bomb을 NULL로 하자
        delete bomb;
        bomb = NULL;
    }

    // 딸기를 없애는(=먹는) 함수
    void SnakeGame::eatStrawberry()
    {   
        // 우선 보드에 기존의 딸기 위치에다가 ' ' add한다
        board.add(strawberry->getY(), strawberry->getX(), ' ');

        // 동적할당 했었던 딸기 없애고 딸기를 NULL로 하자
        delete strawberry;
        strawberry = NULL;
    }

    // stage 번호에 따라서 게임 창을 초기화하는 함수
    void SnakeGame::setStage(int stageNum)
    {
        board.initialize(stageNum);
    }

    // 현재 게임이 스테이지 몇인지 get하는 함수
    int SnakeGame::getStageNum()
    {
        return board.getStageNum();
    }

    // 게임 오버 됐는지 확인하는 함수
    bool SnakeGame::isOver()
    {
        return game_over;
    }

    // 게임 오버를 설정하는 함수
    void SnakeGame::setGameOver(bool on)
    {
        game_over = on;
    }

    // 게임 새로고침
    void SnakeGame::redraw()
    {
        board.refresh();
    }

    // ==혜인님 코드 (일정 시간 지나면 아이템 업데이트 기능)==
    // item update per 7seconds
    void SnakeGame::ItemUpdate()
    {
        if (apple != NULL) {
            // board.add(apple->getY(), apple->getX(), ' ');
            // delete apple;
            // apple = NULL;

            // 기존 코드가 eatApple()과 똑같아서 대체함
            eatApple();
            createApple();
        }

        if (bomb != NULL) {
            // board.add(bomb->getY(), bomb->getX(), ' ');
            // delete bomb;
            // bomb = NULL;

            // 기존 코드가 eatBomb()과 똑같아서 대체함
            eatBomb();
            createBomb();
        }

        if (strawberry != NULL) {
            eatStrawberry();
            createStrawberry();
        }

        if((melon!=NULL) && (board.getStageNum()!=0))
        {
            board.add(melon->getY(), melon->getX(), ' ');
            delete melon;
            melon =NULL;
            createMelon();
        }

        // 스테이지 0에서는 deleteItem()을 실행할 필요가 없다. 아이템 자체가 3개니까
        if (board.getStageNum() != 0)
            deleteItem();
    }
    // ==============================================

    // 4개 아이템 중 하나 랜덤으로 골라서 게임 창에 미반영 한다
    void SnakeGame::deleteItem()
    {
        int deleteItemNum = rand() %4;

        switch (deleteItemNum)
        {
        case 0:
            board.add(apple->getY(), apple->getX(), ' ');
            break;
        case 1:
            board.add(bomb->getY(), bomb->getX(), ' ');
            break;
        case 2:
            board.add(strawberry->getY(), strawberry->getX(), ' ');
            break;
        case 3:
            board.add(melon->getY(), melon->getX(), ' ');
            break;
        }
    }

    void SnakeGame::endWarp()
    {
        board.add(warp1->getY(), warp1->getX(), '1');
        delete warp1;
        warp1=NULL;

        board.add(warp2->getY(), warp2->getX(), '1');
        delete warp2;
        warp2=NULL;
    }

    void SnakeGame::checkWarp(SnakePiece& next, Warp *warp)
    {
        int dy[4]={}, dx[4]={};
        Direction key[5];

        if (snake.getDirection() == up) {
            // UP, RIGHT, LEFT, DOWN
            dx[0] = 0; dy[0] = -1; key[0] = up;
            dx[1] = 1; dy[1] = 0; key[1] = right;
            dx[2] = -1; dy[2] = 0; key[2] = left;
            dx[3] = 0; dy[3] = 1; key[3] = down;
        } 
        else if (snake.getDirection() == down) {
            // DOWN, LEFT, RIGHT, UP
            dx[0] = 0; dy[0] = 1; key[0] = down;
            dx[1] = -1; dy[1] = 0; key[1] = left;
            dx[2] = 1; dy[2] = 0; key[2] = right;
            dx[3] = 0; dy[3] = -1; key[3] = up;
        } 
        else if (snake.getDirection() == right) {
            // RIGHT, DOWN, UP, LEFT
            dx[0] = 1; dy[0] = 0; key[0] = right;
            dx[1] = 0; dy[1] = 1; key[1] = down;
            dx[2] = 0; dy[2] = -1; key[2] = up;
            dx[3] = -1; dy[3] = 0; key[3] = left;
        } 
        else if (snake.getDirection() == left) {
            // LEFT, UP, DOWN, RIGHT
            dx[0] = -1; dy[0] = 0; key[0] = left;
            dx[1] = 0; dy[1] = -1; key[1] = up;
            dx[2] = 0; dy[2] = 1; key[2] = down;
            dx[3] = 1; dy[3] = 0; key[3] = right;
        }

        for(int i=0; i<4; i++)
        {
            int tmp_y= warp->getY()+dy[i];
            int tmp_x= warp->getX()+dx[i];
            //out of map
            if((tmp_y<0)|| (tmp_x<0)|| (tmp_y>20) ||(tmp_x>20))
                continue;
            //if(board.stage[board.stageNum][tmp_y][tmp_x]=='$')
            if(board.getCharAt(tmp_y, tmp_x)=='1' || board.getCharAt(tmp_y, tmp_x)=='2'||board.getCharAt(tmp_y, tmp_x)=='$'||board.getCharAt(tmp_y, tmp_x)=='3')
                continue;

            //if find empty
            snake.setd(key[i]);
            next = SnakePiece(tmp_y, tmp_x);

            break;
        }
    }
}