#include"Define.h"



void col_bala_enemigo(struct jugador player, struct enemy_ enem[max_enemy], int num_enem, int cant_disparos, struct bala_player disparos_ply[max_disparos_ply], int* ii, int* kk, int* activar_col, struct jefe boss,int nivel_mapa);
struct enemy_ crear_enemgios(struct enemy_ enem, int num_enem,int nivel_mapa);
void init();
void col_bala_jugador(struct jugador player, struct bala_ disparos[], int omega[], int orientacion_jugador, int col_jug_enem[], int ajuste, int* activar_col, int* ii, struct balas_boss disparos_boss[]);
float error_x_jugador(int omega[16], int orientacion_jugador);
float error_y_jugador(int omega[16], int orientacion_jugador);
void col_enem_jugador(struct jugador player, struct enemy_ enem[], int omega[], int orientacion_jugador, int num_enem, int ajuste, int col_jug_enem[], int* activar_col, int* ii);
struct bala_ crear_balas(struct bala_ disparos[], struct enemy_ enem[], int j,int nivel_mapa);
void reset_enem(struct enemy_ enem[]);
void reset_disparos(struct bala_ disparos[]);
void reset_torretas(struct enemy2 torretas[]);
void angulo_rot_torreta(struct jugador player, struct enemy2 torretas[], int cont, float* angulo1);
struct misil crear_misiles(struct enemy2 torretas[], struct misil misiles[], int cont, int nivel_mapa,int i);
void col_misil_jugador(struct jugador player, struct misil misiles[], int omega[], int orientacion_jugador, int col_jug_enem[], int cont, int ajuste, int* activar_col, int* ii);
bool activar_sond_disparo(struct enemy_ enem[], int num_enem, bool sonido_disparo);
bool activar_sond_misil(struct enemy2 torretas[], int cont, bool activar_sonido2);
struct jugador crear_balas_jugador(struct jugador player, int omega[], int cant_disparos, int cont1[]);
void ordenar_ranking(struct rank ranking[], int indice, int puntaje, const char* nombre);
void col_ventana(struct jugador player, int* i, int angulo_y, int angulo_x);
void reset_general(int* n, int* llave_x, int* llave_y, int* d, int* e, int* f1, int* g, int* h);
struct jefe moviento_jefe(struct jefe boss, int posicion);
void leeranking(struct rank ranking[], int* Nreal);
void muestraranking(struct rank ranking[], int Nreal);
void grabaranking(struct rank ranking[], int Nreal);
void col_bala_boss(struct jugador player, struct jefe boss, int cant_disparos, int nivel_mapa, int* ii, int* activar_col);






void col_bala_boss(struct jugador player, struct jefe boss, int cant_disparos,int nivel_mapa, int* ii, int* activar_col)
{
	*activar_col = 0;
	int i;
	for (i = 0; i < cant_disparos; i++)
	{
		if (nivel_mapa == 7)
		{
			if (player.disparos_ply[i].pos_x >= boss.pos_x - 108 && player.disparos_ply[i].pos_x <= boss.pos_x + 108)
			{
				if (player.disparos_ply[i].pos_y >= boss.pos_y - 108 && player.disparos_ply[i].pos_y <= boss.pos_y + 108)
				{
					player.disparos_ply[i].pos_y = 2000;
					player.disparos_ply[i].pos_x = 2000;
					player.disparos_ply[i].vel_x = 0;
					player.disparos_ply[i].vel_y = 0;
					*activar_col = 1;
					*ii = i;
				}

			}

		}
	}
	
}

void reset_general(int*n, int*llave_x, int*llave_y, int*d, int*e, int*f1, int*g, int*h)
{
	*n = 1;
	*llave_x = -500;
	*llave_y = -500;
	*d = 0;
	*e = 0;
	*f1 = 0;
	*g = 0;
	*h = 0;
}

void col_ventana(struct jugador player, int *i,int angulo_y,int angulo_x)
{
	*i = 0;
	if (player.y - angulo_y <= -5 || player.y - angulo_y >= 730)
	{
		*i = 1;
	}
	if (player.x + angulo_x <= -5 || player.x + angulo_x >= 1290)
	{
		*i = 1;
	}
}

void init()
{
	al_init();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_mouse();
	al_init_primitives_addon();
	al_install_audio();
	al_init_acodec_addon();
}
struct enemy_ crear_enemgios(struct enemy_ enem, int num_enem,int nivel_mapa)
{
	switch (nivel_mapa)
	{
	case 0:
		enem.pos_x = 50 + rand() % 300;
		enem.pos_y = 800;
		enem.vel_x = 0;
		enem.vel_y = -vel_enemy;
		enem.ndisparos = 0;
		enem.flag = 0;
		enem.angulo = 0;
		break;
	case 1:
		enem.pos_x = 900 + rand() % 300;
		enem.pos_y = 0;
		enem.vel_x = 0;
		enem.vel_y = vel_enemy;
		enem.ndisparos = 0;
		enem.flag = 0;
		enem.angulo = 180 * f;
		break;
	case 2: 
		enem.pos_x = 1350;
		enem.pos_y = 600 + rand() % 120;
		enem.vel_x = -vel_enemy;
		enem.vel_y = 0;
		enem.ndisparos = 0;
		enem.flag = 0;
		enem.angulo = 270 * f;
		break;
	case 3:
		enem.pos_x = 1100 + rand() % 500;
		enem.pos_y = -100;
		enem.angulo = 225 * f;
		enem.vel_x = -vel_enemy * sin(45*f);
		enem.vel_y = vel_enemy * cos(45*f);
		enem.ndisparos = 0;
		enem.flag = 0;
		break;
	case 4:
		enem.pos_x = 50 + rand() % 300;
		enem.pos_y = 800;
		enem.vel_x = 0;
		enem.vel_y = -vel_enemy;
		enem.ndisparos = 0;
		enem.flag = 0;
		enem.angulo = 0;
		break;
	case 5:
		enem.pos_x = -100;
		enem.pos_y = 50 + rand()% 200;
		enem.vel_x = vel_enemy;
		enem.vel_y = 0;
		enem.ndisparos = 0;
		enem.flag = 0;
		enem.angulo = 90*f;
		break;
	case 6:
		enem.pos_x = 50 + rand() % 300;
		enem.pos_y = 800;
		enem.vel_x = 0;
		enem.vel_y = -vel_enemy;
		enem.ndisparos = 0;
		enem.flag = 0;
		enem.angulo = 0;
	}
	
	
		
	return enem;

}

void col_bala_enemigo(struct jugador player, struct enemy_ enem[max_enemy], int num_enem, int cant_disparos, struct bala_player disparos_ply[max_disparos_ply], int* ii, int* kk,int *activar_col, struct jefe boss,int nivel_mapa)
{
	*activar_col = 0;

	for (int k = 1; k <= num_enem; k++)
	{
		for (int i = 0; i <= cant_disparos; i++)
		{
			if (player.disparos_ply[i].pos_x >= enem[k].pos_x - 20 && player.disparos_ply[i].pos_x <= enem[k].pos_x + 20)
			{
				if (player.disparos_ply[i].pos_y >= enem[k].pos_y - 75 && player.disparos_ply[i].pos_y <= enem[k].pos_y + 75 )
				{
					player.disparos_ply[i].pos_y = 2000;
					player.disparos_ply[i].pos_x = 2000;
					player.disparos_ply[i].vel_x = 0;
					player.disparos_ply[i].vel_y = 0;
					*activar_col = 1;
					*ii = i;
					*kk = k;
				}
				
			}
			if (enem[k].angulo == 270 * f || enem[k].angulo == 90 * f)
			{
				if (player.disparos_ply[i].pos_x >= enem[i].pos_x - 75 && player.disparos_ply[i].pos_x <= enem[i].pos_x + 75)
				{
					if (player.disparos_ply[i].pos_y >= enem[i].pos_y - 20 && player.disparos_ply[i].pos_y <= enem[i].pos_y + 20)
					{
						player.disparos_ply[i].pos_y = 2000;
						player.disparos_ply[i].pos_x = 2000;
						player.disparos_ply[i].vel_x = 0;
						player.disparos_ply[i].vel_y = 0;
						*activar_col = 1;
						*ii = i;
						*kk = k;

					}

				}
			}
		}
	}	
}
void col_bala_jugador(struct jugador player, struct bala_ disparos[], int omega[], int orientacion_jugador, int col_jug_enem[], int ajuste, int* activar_col, int* ii, struct balas_boss disparos_boss[])
{
	*activar_col = 0;

	for (int i = 1; i <= max_disparos; i++)
	{
		
		if (disparos[i].x <= (player.x + 100 * sin(col_jug_enem[orientacion_jugador - ajuste] * f)) + error_x_jugador(omega, orientacion_jugador) && disparos[i].x >= (player.x - 100 * sin(col_jug_enem[orientacion_jugador - ajuste] * f)) - error_x_jugador(omega, orientacion_jugador))
		{
			if (disparos[i].y >= (player.y - 100 * cos(col_jug_enem[orientacion_jugador - ajuste] * f)) - error_y_jugador(omega, orientacion_jugador) && disparos[i].y <= (player.y + 100 * cos(col_jug_enem[orientacion_jugador - ajuste] * f)) + error_y_jugador(omega, orientacion_jugador))
			{
				*activar_col = 1;
				*ii = i;

			}
		}
		if (omega[orientacion_jugador] == 180)
		{
			if (disparos[i].x >= (player.x + 100 * sin(col_jug_enem[orientacion_jugador - ajuste] * f)) + error_x_jugador(omega, orientacion_jugador) && disparos[i].x <= (player.x - 100 * sin(col_jug_enem[orientacion_jugador - ajuste] * f)) - error_x_jugador(omega, orientacion_jugador))
			{
				if (disparos[i].y >= (player.y - 100 * cos(col_jug_enem[orientacion_jugador - ajuste] * f)) - error_y_jugador(omega, orientacion_jugador) && disparos[i].y <= (player.y + 100 * cos(col_jug_enem[orientacion_jugador - ajuste] * f)) + error_y_jugador(omega, orientacion_jugador))
				{
					*activar_col = 1;
					*ii = i;
				}
			}
		}



		if (disparos_boss[i].x <= (player.x + 100 * sin(col_jug_enem[orientacion_jugador - ajuste] * f)) + error_x_jugador(omega, orientacion_jugador) && disparos_boss[i].x >= (player.x - 100 * sin(col_jug_enem[orientacion_jugador - ajuste] * f)) - error_x_jugador(omega, orientacion_jugador))
		{
			if (disparos_boss[i].y >= (player.y - 100 * cos(col_jug_enem[orientacion_jugador - ajuste] * f)) - error_y_jugador(omega, orientacion_jugador) && disparos_boss[i].y <= (player.y + 100 * cos(col_jug_enem[orientacion_jugador - ajuste] * f)) + error_y_jugador(omega, orientacion_jugador))
			{
				*activar_col = 1;
				*ii = i;

			}
		}
		if (omega[orientacion_jugador] == 180)
		{
			if (disparos_boss[i].x >= (player.x + 100 * sin(col_jug_enem[orientacion_jugador - ajuste] * f)) + error_x_jugador(omega, orientacion_jugador) && disparos_boss[i].x <= (player.x - 100 * sin(col_jug_enem[orientacion_jugador - ajuste] * f)) - error_x_jugador(omega, orientacion_jugador))
			{
				if (disparos_boss[i].y >= (player.y - 100 * cos(col_jug_enem[orientacion_jugador - ajuste] * f)) - error_y_jugador(omega, orientacion_jugador) && disparos_boss[i].y <= (player.y + 100 * cos(col_jug_enem[orientacion_jugador - ajuste] * f)) + error_y_jugador(omega, orientacion_jugador))
				{
					*activar_col = 1;
					*ii = i;
				}
			}
		}
	}
}
void col_enem_jugador(struct jugador player, struct enemy_ enem[], int omega[], int orientacion_jugador, int num_enem, int ajuste, int col_jug_enem[], int* activar_col, int* ii)
{
	*activar_col = 0;

	for (int i = 1; i <= num_enem; i++)
	{
		if (enem[i].pos_x + 20 - 75 * sin(enem[i].angulo) <= (player.x + 100 * sin(col_jug_enem[orientacion_jugador - ajuste] * f)) + error_x_jugador(omega, orientacion_jugador) && enem[i].pos_x - 20 + 75 * sin(enem[i].angulo) >= (player.x - 100 * sin(col_jug_enem[orientacion_jugador - ajuste] * f)) - error_x_jugador(omega, orientacion_jugador))
		{
			if (enem[i].pos_y + 75 * cos(enem[i].angulo) >= (player.y - 100 * cos(col_jug_enem[orientacion_jugador - ajuste] * f)) - error_y_jugador(omega, orientacion_jugador) && enem[i].pos_y - 75 * cos(enem[i].angulo) <= (player.y + 100 * cos(col_jug_enem[orientacion_jugador - ajuste] * f)) + error_y_jugador(omega, orientacion_jugador))
			{
				*activar_col = 1;
				*ii = i;
			}
		}
	}

}
struct bala_ crear_balas(struct bala_ disparos[], struct enemy_ enem[], int j,int nivel_mapa)
{
	switch (nivel_mapa)
	{
	case 0:
		disparos[enem[j].ndisparos].x = enem[j].pos_x;
		disparos[enem[j].ndisparos].y = enem[j].pos_y - 39;
		disparos[enem[j].ndisparos].vel_x = speed_bala;
		disparos[enem[j].ndisparos].vel_y = 0;
		disparos[enem[j].ndisparos].angulo = 0;
		break;
	case 1:
		disparos[enem[j].ndisparos].x = enem[j].pos_x;
		disparos[enem[j].ndisparos].y = enem[j].pos_y + 39;
		disparos[enem[j].ndisparos].vel_x = -speed_bala;
		disparos[enem[j].ndisparos].vel_y = 0;
		disparos[enem[j].ndisparos].angulo = 180*f;
		break;
	case 2:
	{
		disparos[enem[j].ndisparos].x = enem[j].pos_x - 39;
		disparos[enem[j].ndisparos].y = enem[j].pos_y;
		disparos[enem[j].ndisparos].vel_x = 0;
		disparos[enem[j].ndisparos].vel_y = -speed_bala;
		disparos[enem[j].ndisparos].angulo = 270 * f;
		break;
	}
	case 3:
		disparos[enem[j].ndisparos].x = enem[j].pos_x - 39;
		disparos[enem[j].ndisparos].y = enem[j].pos_y + 20;
		disparos[enem[j].ndisparos].angulo = -135 * f;
		disparos[enem[j].ndisparos].vel_x = -speed_bala * sin(45*f);
		disparos[enem[j].ndisparos].vel_y = -speed_bala * cos(45*f);
		break;
	case 4:
		disparos[enem[j].ndisparos].x = enem[j].pos_x;
		disparos[enem[j].ndisparos].y = enem[j].pos_y - 39;
		disparos[enem[j].ndisparos].vel_x = speed_bala;
		disparos[enem[j].ndisparos].vel_y = 0;
		disparos[enem[j].ndisparos].angulo = 0;
		break;
	case 5:
		disparos[enem[j].ndisparos].x = enem[j].pos_x + 39;
		disparos[enem[j].ndisparos].y = enem[j].pos_y;
		disparos[enem[j].ndisparos].vel_x = 0;
		disparos[enem[j].ndisparos].vel_y = speed_bala;
		disparos[enem[j].ndisparos].angulo = 90 * f;
		break;
	case 6:
		disparos[enem[j].ndisparos].x = enem[j].pos_x;
		disparos[enem[j].ndisparos].y = enem[j].pos_y - 39;
		disparos[enem[j].ndisparos].vel_x = speed_bala;
		disparos[enem[j].ndisparos].vel_y = 0;
		disparos[enem[j].ndisparos].angulo = 0;
		break;
	}
	


	return disparos[enem[j].ndisparos];
	
}
void reset_disparos(struct bala_ disparos[])
{
	int i;
	for (i = 0; i < max_disparos; i++)
	{
		disparos[i].vel_x = 0;
		disparos[i].vel_y = 0;
		disparos[i].x = 0;
		disparos[i].y = 0;

	}
}
void reset_enem(struct enemy_ enem[])
{
	int i;
	for (i = 0; i < max_enemy; i++)
	{
		enem[i].ndisparos = 0;
		enem[i].pos_x = 0;
		enem[i].pos_y = 0;
		enem[i].vel_x = 0;
		enem[i].vel_y = 0;
		enem[i].ndisparos = 0;
		enem[i].flag = 0;
		enem[i].vida = 0;
	}
	
}
float error_x_jugador(int omega[16], int orientacion_jugador)
{
	float error_x;
	if (omega[orientacion_jugador] == 0 || omega[orientacion_jugador] == 90 || omega[orientacion_jugador] == 180 || omega[orientacion_jugador] == 270)
	{
		error_x = 30 * cos(omega[orientacion_jugador] * f);
	}
	else
	{
		error_x = 0;
	}
	return error_x;
}
float error_y_jugador(int omega[16], int orientacion_jugador)
{
	float error_y;
	if (omega[orientacion_jugador] == 0 || omega[orientacion_jugador] == 90 || omega[orientacion_jugador] == 180 || omega[orientacion_jugador] == 270)
	{
		error_y = 30 * sin(omega[orientacion_jugador] * f);
	}
	else
	{
		error_y = 0;
	}
	return error_y;
}
void angulo_rot_torreta(struct jugador player, struct enemy2 torretas[], int cont, float* angulo1)
{
	
	int i = 0;
	for (int i = 0; i < cont; i++)
	{
		angulo1[i] = -asin((player.y - torretas[i].y) / (sqrt((player.y - torretas[i].y) * (player.y - torretas[i].y) + (torretas[i].x - player.x) * (torretas[i].x - player.x))));
		if (angulo1[i] >= -90 * f && angulo1[i] <= 0)
		{
			angulo1[i] = -acos((torretas[i].x - player.x) / (sqrt((player.y - torretas[i].y) * (player.y - torretas[i].y) + (torretas[i].x - player.x) * (torretas[i].x - player.x))));
			
		}
		if (angulo1[i] >= 0 && angulo1[i] <= 90 * f)
		{
			angulo1[i] = -acos((torretas[i].x - player.x) / (sqrt((player.y - torretas[i].y) * (player.y - torretas[i].y) + (torretas[i].x - player.x) * (torretas[i].x - player.x))));
			angulo1[i] = angulo1[i] * -1;
		}
	}	
}
void reset_torretas(struct enemy2 torretas[])
{
	for (int i = 0; i < max_enemy; i++)
	{
		torretas[i].x = 0;
		torretas[i].y = 0;
		torretas[i].vida = 0;
	}
}
struct misil crear_misiles(struct enemy2 torretas[], struct misil misiles[],int cont,int nivel_mapa,int i)
{
	float angulo[10];
	angulo_rot_torreta(player, torretas, cont, angulo);
	misiles[i].x = torretas[i].x;
	misiles[i].y = torretas[i].y;
	misiles[i].angulo = angulo[i];
	misiles[i].vel_x = vel_misiles * cos(angulo[i]);
	misiles[i].vel_y = vel_misiles * sin(angulo[i]);
	return misiles[i];
		
}
void col_misil_jugador(struct jugador player, struct misil misiles[], int omega[], int orientacion_jugador, int col_jug_enem[], int cont,int ajuste, int* activar_col, int* ii)
{
	*activar_col = 0;
	for (int i = 0; i < cont; i++)
	{


		if (misiles[i].x <= (player.x + 100 * sin(col_jug_enem[orientacion_jugador - ajuste] * f)) + error_x_jugador(omega, orientacion_jugador) && misiles[i].x >= (player.x - 100 * sin(col_jug_enem[orientacion_jugador - ajuste] * f)) - error_x_jugador(omega, orientacion_jugador))
		{
			if (misiles[i].y >= (player.y - 100 * cos(col_jug_enem[orientacion_jugador - ajuste] * f)) - error_y_jugador(omega, orientacion_jugador) && misiles[i].y <= (player.y + 100 * cos(col_jug_enem[orientacion_jugador - ajuste] * f)) + error_y_jugador(omega, orientacion_jugador))
			{
				*activar_col = 1;
				*ii = i;
				
			}
		}
		if (omega[orientacion_jugador] == 180)
		{
			if (misiles[i].x >= (player.x + 100 * sin(col_jug_enem[orientacion_jugador - ajuste] * f)) + error_x_jugador(omega, orientacion_jugador) && misiles[i].x <= (player.x - 100 * sin(col_jug_enem[orientacion_jugador - ajuste] * f)) - error_x_jugador(omega, orientacion_jugador))
			{
				if (misiles[i].y >= (player.y - 100 * cos(col_jug_enem[orientacion_jugador - ajuste] * f)) - error_y_jugador(omega, orientacion_jugador) && misiles[i].y <= (player.y + 100 * cos(col_jug_enem[orientacion_jugador - ajuste] * f)) + error_y_jugador(omega, orientacion_jugador))
				{
					*activar_col = 1;
					*ii = i;
				}
			}
		}
		
	}
}
bool activar_sond_disparo(struct enemy_ enem[], int num_enem, bool sonido_disparo)
{
	int i = 0;
	sonido_disparo = false;
	for (i = 1; i <= num_enem; i++)
	{
		if (enem[num_enem].pos_x > 0 && enem[num_enem].pos_x < 1280)
		{
			if (enem[num_enem].pos_y > 0 && enem[num_enem].pos_y < 720)
			{
				sonido_disparo = true;
			}
		}
	}
	return sonido_disparo;
}
bool activar_sond_misil(struct enemy2 torretas[], int cont,bool activar_sonido2)
{
	int i;
	activar_sonido2 = false;
	for (i = 0; i < cont; i++)
	{
		if (torretas[i].vida == 0)
		{
			activar_sonido2 = true;
		}
	}
	return activar_sonido2;
}
struct jugador crear_balas_jugador(struct jugador player, int omega[], int cant_disparos, int cont1[])
{
	player.disparos_ply[cant_disparos].pos_y = player.y - 54 * cos(omega[cont1[cant_disparos]] * f);
	player.disparos_ply[cant_disparos].pos_x = player.x + 53 * sin(omega[cont1[cant_disparos]] * f);

	player.disparos_ply[cant_disparos].vel_x = speed_bala * cos(omega[cont1[cant_disparos]] * f);
	player.disparos_ply[cant_disparos].vel_y = speed_bala * sin(omega[cont1[cant_disparos]] * f);

	return player;
}
struct jefe moviento_jefe(struct jefe boss, int posicion)
{
	switch (posicion)
	{
	case 0:
		boss.pos_x = 1380;
		boss.pos_y = player.y;
		boss.vel_x = -boss_speed;
		boss.vel_y = 0;
		boss.angulo = -90 * f;
		boss.ndisparos = 0;
		break;
	case 1:
		boss.pos_y = -100;
		boss.pos_x = player.x;
		boss.vel_y = boss_speed;
		boss.vel_x = 0;
		boss.angulo = 180 * f;
		boss.ndisparos = 0;
		break;
	case 2:
		boss.pos_x = 1380;
		boss.ndisparos = 0;
		break;
	}
	return boss;
}





void leeranking(struct rank ranking[], int* Nreal)
{
	FILE* franking;
	*Nreal = 0;
	if ((franking = fopen("ranking.txt", "r")) == NULL)
	{
		printf("Error al abrir archivo!!");
		exit(-1);
	}
	while (!feof(franking))
	{
		fscanf(franking, "%s", ranking[*Nreal].nombre);
		fscanf(franking, "%d", &ranking[*Nreal].puntaje);
		(*Nreal)++;
	}
	fclose(franking);
}

void muestraranking(struct rank ranking[], int Nreal)
{
	int i;
	for (i = 0; i <= Nreal; i++)
	{
		printf("%s %d\t", ranking[i].nombre, ranking[i].puntaje);
		printf("\n");
				
	}
}

void grabaranking(struct rank ranking[], int Nreal)
{
	FILE* franking;
	int i, count;
	if ((franking = fopen("ranking.txt", "w")) == NULL)
	{
		printf("Error al abrir archivo!!");
		return;
	}
	if (Nreal < 6)
	{
		count = Nreal;
	}
	else
	{
		count = 5;
	}
	for (i = 0; i < count; i++)
	{
		if (i < Nreal)
			fprintf(franking, "%s %d\n", ranking[i].nombre, ranking[i].puntaje);
		else
			fprintf(franking, "%s %d", ranking[i].nombre, ranking[i].puntaje);
	}
	fclose(franking);
}

void ordenar_ranking(struct rank ranking[], int indice, int puntaje, char nombre[])
{
	struct rank puntaje_actual;
	struct rank aux1;
	int i;

	strcpy(puntaje_actual.nombre, nombre);
	puntaje_actual.puntaje = puntaje;
	if(indice < 6)
	{
		ranking[indice+1] = puntaje_actual;
	}
	for (i = 0; i <= indice; i++)
	{
		if (puntaje_actual.puntaje > ranking[i].puntaje)
		{
			aux1 = ranking[i];
			ranking[i] = puntaje_actual;
			puntaje_actual = aux1;
		}
	}
	
}



