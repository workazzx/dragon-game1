#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int hp = 100;
    int zel = 2;
    int sila = 3;
    int dhp = 150;
    int zlost = 0;
    int c, real, shown, d, dmg, block, roll;

    srand(time(0));

    while (hp > 0 && dhp > 0) {
        printf("\nhp %d | зелья %d | сила %d | дракон %d\n", hp, zel, sila, dhp);

        real = rand() % 3;
        shown = real;
        if (rand() % 100 < 25) shown = rand() % 3;

        if (shown == 0) printf("дракон набирает воздух\n");
        if (shown == 1) printf("дракон пригнулся\n");
        if (shown == 2) printf("дракон задрал голову\n");

        printf("1 удар, 2 блок, 3 перекат, 4 зелье, 5 отдых\n> ");
        if (scanf("%d", &c) != 1) break;

        block = 0;
        roll = 0;

        if (c == 1 && sila > 0) {
            d = 15 + rand() % 11;
            sila = sila - 1;
            dhp = dhp - d;
            printf("попал, -%d\n", d);
        } else if (c == 2) {
            block = 1;
        } else if (c == 3) {
            roll = 1;
        } else if (c == 4 && zel > 0) {
            zel = zel - 1;
            hp = hp + 35;
            if (hp > 100) hp = 100;
            printf("выпил зелье\n");
        } else if (c == 5) {
            sila = sila + 2;
            if (sila > 3) sila = 3;
            printf("отдышался\n");
        } else {
            printf("промазал\n");
        }

        if (dhp > 0) {
            if (zlost == 0 && dhp <= 75) {
                zlost = 1;
                printf("дракон разозлился\n");
            }

            if (real == 0) {
                dmg = 25;
                if (zlost) dmg = dmg * 14 / 10;
                if (block) dmg = dmg / 2;
                if (roll) dmg = dmg * 7 / 10;
                printf("дракон дунул огнём\n");
            } else if (real == 1) {
                dmg = 18;
                if (zlost) dmg = dmg * 14 / 10;
                if (block) dmg = dmg / 5;
                if (roll) dmg = 0;
                printf("дракон ударил лапой\n");
            } else {
                dmg = 8;
                if (zlost) dmg = dmg * 14 / 10;
                if (roll) dmg = 0;
                if (!block) {
                    sila = sila - 1;
                    if (sila < 0) sila = 0;
                    printf("от рёва пропала сила\n");
                }
            }

            hp = hp - dmg;
            if (dmg > 0) printf("тебе -%d\n", dmg);
        }
    }

    if (hp > 0) printf("\nпобеда\n");
    else printf("\nты проиграл\n");

    return 0;
}
