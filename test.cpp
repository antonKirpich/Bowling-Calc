#include "test.h"

//тест когда все 10 бросков мимо - Looser Game
TEST(TotalCalcTest, TenZeroThrows)
{
    std::vector<Frame> game;
    game.reserve(11);

    for (int frame = 0; frame < 10; frame++)
    {
        Frame *shot = new Frame(0, 0);  //все броски нулевые
        game.push_back(*shot);
    }
    auto it = game.begin();
    int total = CalcTotalScore(it, 9);
    ASSERT_EQ(total, 0);    //ожидаемый результат 0
    game.clear();
}

//тест когда каждым броском выбивается по 1 кегле, без страйков и спаре
TEST(TotalCalcTest, OneThrowOnePoint)
{
    std::vector<Frame> game;
    game.reserve(11);

    for (int frame = 0; frame < 10; frame++)
    {
        Frame *shot = new Frame(1, 1);
        game.push_back(*shot);
    }
    auto it = game.begin();
    int total = CalcTotalScore(it, 9);
    ASSERT_EQ(total, 20);      //ожидаемый результат 20
    game.clear();
}

//тест из задания
TEST(TotalCalcTest, ThrowsFromTest)
{
    std::vector<Frame> game;
    game.reserve(11);

    Frame *shot = new Frame(10, 0);     game.push_back(*shot);
    shot = new Frame(7,3);  game.push_back(*shot);
    shot = new Frame(7,2);  game.push_back(*shot);
    shot = new Frame(9,1);  game.push_back(*shot);
    shot = new Frame(10,0); game.push_back(*shot);
    shot = new Frame(10,0); game.push_back(*shot);
    shot = new Frame(10,0); game.push_back(*shot);
    shot = new Frame(2,3);  game.push_back(*shot);
    shot = new Frame(6,4);  game.push_back(*shot);
    shot = new Frame(7,3);  game.push_back(*shot);
    shot = new Frame(3,0);  game.push_back(*shot); //бонусный бросок в 10м фрейме

    auto it = game.begin();
    int total = CalcTotalScore(it, 10);
    ASSERT_EQ(total, 168);      //ожидаемый результат 168
    game.clear();
}

//тест кастом
TEST(TotalCalcTest, CustomTest2)
{
    std::vector<Frame> game;
    game.reserve(11);

    Frame *shot = new Frame(5, 5);     game.push_back(*shot);
    shot = new Frame(10,0);  game.push_back(*shot);
    shot = new Frame(3,6);  game.push_back(*shot);
    shot = new Frame(10,0);  game.push_back(*shot);
    shot = new Frame(10,0); game.push_back(*shot);
    shot = new Frame(0,0); game.push_back(*shot);
    shot = new Frame(3,7); game.push_back(*shot);
    shot = new Frame(4,2);  game.push_back(*shot);
    shot = new Frame(4,5);  game.push_back(*shot);
    shot = new Frame(10,0);  game.push_back(*shot);
    shot = new Frame(3,1);  game.push_back(*shot); //бонусный бросок в 10м фрейме

    auto it = game.begin();
    int total = CalcTotalScore(it, 10);
    ASSERT_EQ(total, 121);      //ожидаемый результат 121
    game.clear();
}

//тест когда все броски - страйки - Perfect Game
TEST(TotalCalcTest, TenStrikeThrows)
{
    std::vector<Frame> game;
    game.reserve(11);

    for (int frame = 0; frame < 10; frame++)
    {
        Frame *shot = new Frame(10, 0);  //все броски страйки
        game.push_back(*shot);
    }

    Frame *shot = new Frame(10, 10); //плюс два бонусных броска в 10м фрейме - тоже оба страйки
    game.push_back(*shot);

    auto it = game.begin();
    int total = CalcTotalScore(it, 10);
    ASSERT_EQ(total, 300);      //ожидаемый результат 300
    game.clear();
}