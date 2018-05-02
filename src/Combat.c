#include "rog.h"

#define PLAYER_ATTACKING 1

int combat(Player* player, Monster* monster, int order)
{
	//Player attacking
	if(order == PLAYER_ATTACKING)
	{
		monster->hp -= player->attack;
		//Monster retaliates if hp > 0
		if(monster->hp>0)
		{
			player->hp -= monster->attack;
		}
		//Monster dies
		else
		{
			killMonster(monster);
			addExp(player, monster->exp);
			//mvprintw(1,0,"Hit %s for %d damage, %s dies!    ",
			//monster->type, player->attack, monster->type);
			return 1;
		}
	}
	//Monster attacking
	else
	{
		player->hp -= monster->attack;
		//Player retaliates if healt > 0
		if(player->hp)
		{
			monster->hp -= player->attack;
		}
	}
	//mvprintw(1,0,"Hit %s for %d damage, remaining hp: %d ",
	//monster->type, player->attack, monster->hp);
	move(player->position->y, player->position->x);

	return 1;
}