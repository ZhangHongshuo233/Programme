#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct card{
    int suit;
    int face; 
};
void deal(struct card *wdeck);
/* 发牌函数声明 */
int main( void ){
    int i;
    struct card deck[52];
    // String arrays for mapping integer codes to text
    const char *suit[ ] = {"Heart", "Diamond", "Club", "Spade"};
    const char *face[ ] = {"A", "K", "Q", "J", "10", "9", "8", "7", "6", "5", "4", "3", "2"};
    deal(deck); 
/* 调用函数，实现发牌 */
for(i = 0; i < 52; i++){
    // Print player header every 13 cards
    if(i%13 == 0) printf("Player %d:\n", i / 13 + 1);
    printf("%s of %s\n", face[deck[i].face], suit[deck[i].suit] );
}
    return 0;
}

/* 
// [对比] 旧版本：交换法洗牌
// 优点：效率高 O(N)
// 缺点：逻辑简单，线性洗牌
void deal(struct card *wdeck){
    int i, j, r;
    struct card temp;
    for(i = 0; i < 52; i++){
        wdeck[i].suit = i / 13;
        wdeck[i].face = i % 13;
    }
    srand((unsigned)time(NULL));
    for(i = 0; i < 52; i++){
        r = rand() % 52;
        temp = wdeck[i];
        wdeck[i] = wdeck[r];
        wdeck[r] = temp;
    }
}
*/

// [对比] 新版本：标记法发牌
void deal(struct card *wdeck) /* 发牌 */{
    int i, m, t;
    // [修正] 去掉 static，否则第二次调用函数时 temp 仍为全 1，会导致死循环
    int temp[52] = {0}; 
    /* 发牌标记 0:未发 1:已发 */
    srand(time(NULL));
    /* 设定随机数的产生与系统时钟关联 */
    for(i = 0; i < 52; i++){
        // [对比] 效率问题：随着空位减少，随机碰撞的效率会降低
        while(1){
            m = rand() % 52; /* 计算机随机产生一个0~51之间的数 */
            if(temp[m] == 0) break;
        }  
    temp[m] = 1;/* 4人轮转发牌 */
    
    // [对比] 逻辑差异：这里模拟了轮流发牌 (Round-Robin)，即每人一张轮着发
    // 公式解析：(i % 4) 决定是第几个玩家，(i / 4) 决定是该玩家的第几张牌
    t = (i % 4) * 13 + (i / 4);
    wdeck[t].suit = m / 13;
    wdeck[t].face = m % 13;
    }
}