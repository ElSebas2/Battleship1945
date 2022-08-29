#include <stdio.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <Windows.h>
#include <math.h>
#include <stdlib.h>
#include<string.h>
#include<string>
#include "Imagenes.h"
#include "Define.h"
#include "Estructuras.h"
#include "Funciones.h"


int main()
{

	FILE* salas[9] = { fopen(map1 , "r"),fopen(map2 , "r") ,fopen(map3, "r") ,fopen(map4 , "r") ,fopen(map5 , "r") ,fopen(map6 , "r") ,fopen(map7 , "r") ,fopen(map8 , "r") ,fopen(map9 , "r") };
	FILE* mini_matriz;///colision con islas
	FILE* item_curacion;///colision con item de cura

	bool victoria = false;
	bool lineas_guia = false;
	float angulo_torretas[10];
	int activar_col1;
	int activar_col2;
	int activar_col3;
	int activar_col4;
	int ajuste = 0;
	float error_x;
	float error_y;
	int angulo_y;
	int angulo_x;
	int contx = 0;
	int dx[15];
	int dy[15];
	bool auxx = false;
	bool reloading = false;
	char mini_mapa[mini_SIZE][mini_SIZE];
	char mapa[SIZE][SIZE];
	char item_cura[mini_SIZE][mini_SIZE];
	char basura;
	int choque[16] = { 0 };
	int fpss = 0;
	bool play = false;
	int puntajes = 0;
	int rachas_ = 1;
	int vida_player = 0;
	int i;
	int aux = 0;
	int num_enem = 0;
	int contt = 1;
	bool freno = true;
	bool disparo = false;
	int x1, y1;
	int k;
	int omega[16];
	int recarga_ = 0;
	int orientacion_jugador = 0;
	int cont1[max_disparos];
	int cant_disparos = 0;
	int llave_x = 0;
	int llave_y = 0;
	int j;
	int n = 0;
	int dx1[100], dy1[100], contx1 = 0;
	int dx5[500], dy5[500], eee = 0;
	int cont = 0;
	int repara = 0;
	int cantFrame_Disparo = 0;
	int cantFrame_Fuego = 0;
	int cantFrame_Humo = 0;
	bool animacion = false;
	int animacion_x, animacion_y;
	int col_jug_enem[5];
	int nivel_mapa = 0;
	int disp_misiles = 0;
	bool aux1 = false;
	int cambio = 0;
	bool muerte = false;
	bool sonido_disparo = false;
	bool sonido_misil1 = false;
	int grabar = 1;
	int cambiar_pos = 0;
	int indice = 0;
	char nombre[27]= "";
	int choque_vent = 0;
	int pos_boss;
	int activar_cambio = 1;
	int disp_boss = 0;
	int tiempo_disp_boss = 0;
	int cadena = 0;
	int espacio = 0;
	bool instruccion = false;
	bool score = false;
	int c = 0;
	int d = 0;
	bool name = false;
	int activar_col5 = 0;
	bool inmortal = false;
	int segundo = 0;
	bool cambio_nivel = false;
	init();




	int ancho = GetSystemMetrics(SM_CXSCREEN);
	int alto = GetSystemMetrics(SM_CYSCREEN);

	item_curacion = fopen("Mapas/llave.txt", "r");
	mini_matriz = fopen("Mapas/isla.txt", "r");
	if (mini_matriz == NULL)
	{
		printf("Error al abrir archivo!!");
		exit(-1);
	}
	if (item_curacion  == NULL)
	{
		printf("Error al abrir archivo!!");
		exit(-1);
	}
	

	for (i = 0; i < mini_SIZE; i++)
	{
		for (j = 0; j < mini_SIZE; j++)
		{
			fscanf(mini_matriz, "%c", &mini_mapa[i][j]);
		}
		fscanf(mini_matriz, "%c", &basura);
	}

	for (i = 0; i < mini_SIZE; i++)
	{
		for (j = 0; j < mini_SIZE; j++)
		{
			fscanf(item_curacion, "%c", &item_cura[i][j]);
		}
		fscanf(item_curacion, "%c", &basura);
	}
	
	
	

	fclose(mini_matriz);
	fclose(item_curacion);
	

	
	
	////////////////////////////////////////////////////////   DECLARACION DE SONIDOS Y MUSICA   ////////////////////////////////////////////////////////

	ALLEGRO_SAMPLE* machine_gun = NULL;
	ALLEGRO_SAMPLE* ametralladora = NULL;
	ALLEGRO_SAMPLE* disparo_ = NULL;
	ALLEGRO_SAMPLE* musicas = NULL;
	ALLEGRO_SAMPLE* reparacion = NULL;
	ALLEGRO_SAMPLE* sonido_misil = NULL;
	ALLEGRO_SAMPLE* sonido_enem = NULL;
	ALLEGRO_SAMPLE* menu_musica = NULL;
	ALLEGRO_SAMPLE* muerte_music = NULL;
	ALLEGRO_SAMPLE_INSTANCE* music_muerte = NULL;
	ALLEGRO_SAMPLE_INSTANCE* instans = NULL;
	ALLEGRO_SAMPLE_INSTANCE* music_menu = NULL;


	al_reserve_samples(15);


	machine_gun = al_load_sample(machinegun);
	ametralladora = al_load_sample(disp_avion);
	musicas = al_load_sample(song);
	disparo_ = al_load_sample(disparos_);
	reparacion = al_load_sample(repair);
	sonido_misil = al_load_sample(misil_efect);
	sonido_enem = al_load_sample(disp_enem);
	menu_musica = al_load_sample(musica_para_menu);
	muerte_music = al_load_sample(musica_muerte);


	music_muerte = al_create_sample_instance(muerte_music);
	music_menu = al_create_sample_instance(menu_musica);
	instans = al_create_sample_instance(musicas);

	al_set_sample_instance_playmode(music_menu, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(music_menu, al_get_default_mixer());
	al_set_sample_instance_playmode(instans, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(instans, al_get_default_mixer());
	al_set_sample_instance_playmode(music_muerte, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(music_muerte, al_get_default_mixer());


	//////////////////////////////////////////////////////// DECLACION DE IMAGENES, COLAS, LETRAS, ETC////////////////////////////////////////////////////////

	ALLEGRO_EVENT_QUEUE* cola2 = al_create_event_queue();
	ALLEGRO_EVENT_QUEUE* cola = al_create_event_queue();
	ALLEGRO_BITMAP* torre = al_load_bitmap(torreta);
	ALLEGRO_BITMAP* fondo = al_load_bitmap("Imagenes/fondo.bmp");
	ALLEGRO_BITMAP* vida[6] = { al_load_bitmap(vida1),al_load_bitmap(vida2) ,al_load_bitmap(vida3) ,al_load_bitmap(vida4) ,al_load_bitmap(vida5),al_load_bitmap(vida6) };
	ALLEGRO_BITMAP* jugador[2] = { al_load_bitmap(p0), al_load_bitmap(p1) };
	ALLEGRO_BITMAP* bala1[17] = { al_load_bitmap(bala_derecha), al_load_bitmap(bala112), al_load_bitmap(bala134), al_load_bitmap(bala156), al_load_bitmap(bala_abajo), al_load_bitmap(bala202), al_load_bitmap(bala224), al_load_bitmap(bala246), al_load_bitmap(bala_izquierda), al_load_bitmap(bala292), al_load_bitmap(bala314), al_load_bitmap(bala336),al_load_bitmap(bala_arriba),al_load_bitmap(bala22),al_load_bitmap(bala44),al_load_bitmap(bala68),al_load_bitmap(nulo) };
	ALLEGRO_BITMAP* circulo_ = al_load_bitmap(circulo);
	ALLEGRO_BITMAP* misil = al_load_bitmap(misil_);
	ALLEGRO_BITMAP* humo[4] = { al_load_bitmap(humo1),al_load_bitmap(humo2), al_load_bitmap(humo3), al_load_bitmap(humo4) };
	ALLEGRO_BITMAP* recargas = al_load_bitmap(bala_completa);
	ALLEGRO_BITMAP* enemy1 = al_load_bitmap(enemy1_);
	ALLEGRO_BITMAP* avion = al_load_bitmap(avion_);
	ALLEGRO_BITMAP* disparos_[6] = { al_load_bitmap(disparo1), al_load_bitmap(disparo2), al_load_bitmap(disparo3), al_load_bitmap(disparo4), al_load_bitmap(disparo5), al_load_bitmap(disparo6) };
	ALLEGRO_BITMAP* fuegos_[8] = { al_load_bitmap(fuego1_),al_load_bitmap(fuego2_),al_load_bitmap(fuego3_),al_load_bitmap(fuego4_),al_load_bitmap(fuego5_),al_load_bitmap(fuego6_),al_load_bitmap(fuego7_),al_load_bitmap(fuego8_) };
	ALLEGRO_BITMAP* fuegos[5] = { al_load_bitmap(fuego1),al_load_bitmap(fuego2) ,al_load_bitmap(fuego3) ,al_load_bitmap(fuego4) ,al_load_bitmap(fuego5) };
	ALLEGRO_BITMAP* isla = al_load_bitmap(isla_);
	ALLEGRO_BITMAP* tabla_puntajes = al_load_bitmap(tabla_puntaje);
	ALLEGRO_BITMAP* racha = al_load_bitmap(rachas);
	ALLEGRO_BITMAP* instruct[2] = { al_load_bitmap(instrucciones),al_load_bitmap(instrucciones_play) };
	ALLEGRO_BITMAP* menu[3] = { al_load_bitmap(menu1),al_load_bitmap(menu_play),al_load_bitmap(menu_high) };
	ALLEGRO_BITMAP* high_scores[2] = {al_load_bitmap(leardboard),al_load_bitmap(leardboard_home)};
	ALLEGRO_BITMAP* tempo[3] = { al_load_bitmap(reloj0),al_load_bitmap(reloj1),al_load_bitmap(reloj2) };
	ALLEGRO_BITMAP* flechas = al_load_bitmap(flecha);
	ALLEGRO_BITMAP* game_over[3] = { al_load_bitmap(game),al_load_bitmap(gamesi),al_load_bitmap(gameno) };
	ALLEGRO_COLOR negro = al_map_rgb(0, 0, 0);
	ALLEGRO_BITMAP* winer = al_load_bitmap(win);
	ALLEGRO_COLOR rojo = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR blanco = al_map_rgb(255, 255, 255);
	ALLEGRO_DISPLAY* ventana = al_create_display(2 * ancho / 3, 2 * alto / 3);
	ALLEGRO_TIMER* fps = al_create_timer(1.0 / 5);
	ALLEGRO_TIMER* recarga = al_create_timer(1.0);
	ALLEGRO_TIMER* seg = al_create_timer(1.0);
	ALLEGRO_FONT* letra = al_load_font("Sernes-Light.TTF", 30, 0);
	ALLEGRO_FONT* letra1 = al_load_font("Sernes-Light.TTF", 20, 0);
	ALLEGRO_FONT* letra2 = al_load_font("Sernes-Light.TTF", 60, 0);
	ALLEGRO_FONT* letra3 = al_load_font("Sernes-Light.TTF", 100, 0);
	ALLEGRO_FONT* letra4 = al_load_font("Sernes-Light.TTF", 60, 0);

	ALLEGRO_BITMAP* llave = al_load_bitmap(llave_);



	printf("ANCHO = %d \t ALTO = %d\n", 2 * ancho / 3, 2 * alto / 3);
	al_set_window_title(ventana, "Battleship 1945");
	al_set_window_position(ventana, ancho / 2 - ancho / 3, alto / 2 - alto / 3);
	al_register_event_source(cola, al_get_keyboard_event_source());
	al_register_event_source(cola, al_get_timer_event_source(recarga));
	al_register_event_source(cola, al_get_timer_event_source(fps));
	al_register_event_source(cola2, al_get_timer_event_source(seg));
	al_register_event_source(cola, al_get_mouse_event_source());
	al_register_event_source(cola2, al_get_mouse_event_source());
	al_register_event_source(cola2, al_get_keyboard_event_source());


	al_start_timer(fps);
	al_start_timer(recarga);
	

	//////////////////////////////////////////////////////// INICIALIZANDO ARREGLOS PARA ANGULOS Y VELOCIDADES DEL JUGADOR////////////////////////////////////////////////////////

	srand(time(0));
	omega[0] = 0;
	for (k = 0; k <= 15; k++)
	{
		omega[k] = 22 * k;
		if (omega[k] >= 88)
		{
			omega[k] = omega[k] + 2;
		}
		if (omega[k] >= 178)
		{
			omega[k] = omega[k] + 2;
		}
		if (omega[k] >= 268)
		{
			omega[k] = omega[k] + 2;
		}
	}

	for (i = 0; i < 5; i++)
	{
		col_jug_enem[i] = omega[i];
	}

	for (k = 0; k <= 15; k++)
	{
		player.vel_y[k] = (speed * cos(omega[k] * f));
		player.vel_x[k] = (speed * sin(omega[k] * f));
	}

	
	ALLEGRO_EVENT Evento;
	ALLEGRO_EVENT Evento2;

	leeranking(ranking, &indice);
	//////////////////////////////////////////////////////// COMIENZA EL CICLO ////////////////////////////////////////////////////////
	while (muerte == false)
	{
		al_wait_for_event(cola, &Evento);


		//////////////////////////////////////////////////////// CONFIGURACION MENU PRINCIPAL ////////////////////////////////////////////////////////
		if (play == false && instruccion == false && score == false)
		{
			al_stop_sample_instance(music_muerte);
			al_stop_sample_instance(instans);
			al_play_sample_instance(music_menu);

			al_draw_scaled_bitmap(menu[n], 0, 0, 1900, 1080, 0, 0, al_get_display_width(ventana), al_get_display_height(ventana), 0);
			if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES || Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{

				n = 0;
				x1 = Evento.mouse.x;
				y1 = Evento.mouse.y;

				if (x1 <= 784 && x1 >= 480)
				{
					if (y1 <= 463 && y1 >= 351)
					{
						n = 1;
						if (Evento.mouse.button)
						{
							instruccion = true;
							play = true;
						}
					}
				}
				if (x1 >= 479 && x1 <= 793)
				{
					if (y1 >= 521 && y1 <= 649)
					{
						n = 2;
						if (Evento.mouse.button)
						{
							score = true;
							play = true;
						}
						
					}

				}
			}
			if (Evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				al_destroy_bitmap(jugador[1]);
				al_destroy_bitmap(circulo_);
				al_destroy_bitmap(recargas);
				return 0;
			}
			al_flip_display();
		}

		//////////////////////////////////////////////////////// CONFIGURACION PARA LA PANTALLA DE PUNTAJES ////////////////////////////////////////////////////////
		if (score == true )
		{
			al_draw_scaled_bitmap(high_scores[d], 0, 0, al_get_bitmap_width(high_scores[d]), al_get_bitmap_height(high_scores[d]), 0, 0, al_get_display_width(ventana), al_get_display_height(ventana), 0);
			if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES || Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				d = 0;
				x1 = Evento.mouse.x;
				y1 = Evento.mouse.y;

				if (x1 <= 220 && x1 >= 20)
				{
					if (y1 <= 690 && y1 >= 590)
					{
						d = 1;
						if (Evento.mouse.button)
						{
							score = false;
							play = false;
						}
					}
				}
			}

			for (i = 0; i < indice; i++)
			{
				if (indice >= 5)
				{
					indice = 5;
				}
				if (ranking[i].puntaje != 0)
				{
					al_draw_textf(letra4, blanco, 360, 270 + espacio, 0, "%d) %s  %d", i + 1, ranking[i].nombre, ranking[i].puntaje);
				}				
				espacio = espacio + 80;
				
			}
			espacio = 0;
			al_flip_display();
		}


		//////////////////////////////////////////////////////// CONFIGURACION PARA LA PANTALLA DE INSTUCCIONES ////////////////////////////////////////////////////////
		if (instruccion == true && play == true && score == false)
		{
			al_draw_scaled_bitmap(instruct[c], 0, 0, al_get_bitmap_width(instruct[c]), al_get_bitmap_height(instruct[c]), 0, 0, al_get_display_width(ventana), al_get_display_height(ventana), 0);
			if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES || Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				c = 0;

				x1 = Evento.mouse.x;
				y1 = Evento.mouse.y;
				if (x1 <= 1250 && x1 >= 1030)
				{
					if (y1 <= 710 && y1 >= 610)
					{
						c=1;
						if (Evento.mouse.button)
						{
							instruccion = false;
							play = true;
							name = true;
						}
					}
				}
			}
			
			al_flip_display();
		}
		//////////////////////////////////////////////////////// CONFIGURACION PARA ESCRIBIR EL NOMBRE ANTES DE JUGAR ////////////////////////////////////////////////////////
		if (name == true)
		{
			al_draw_filled_rectangle(0, 0, 1280, 720, negro);
			if (grabar == 1)
			{
				if (cadena <= 7)
				{
					if (Evento.type == ALLEGRO_EVENT_KEY_DOWN)
					{
						if (Evento.keyboard.keycode >= ALLEGRO_KEY_A && Evento.keyboard.keycode <= ALLEGRO_KEY_Z)
						{
							nombre[cadena] += 'a' + (Evento.keyboard.keycode - ALLEGRO_KEY_A);
							cadena++;
						}
					}
				}
				if (Evento.type == ALLEGRO_EVENT_KEY_DOWN)
				{
					if (Evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
					{
						grabar = 0;
						name = false;
					}
				}
				al_draw_text(letra3, blanco, 200 , 300, 0, "Escriba su nombre:");
				al_draw_textf(letra3, blanco, 200, 400, 0, "%s", nombre);

			}
			al_flip_display();
		}
		//////////////////////////////////////////////////////// COMIENZA EL JUEGO ////////////////////////////////////////////////////////

		if (play == true && instruccion == false && score == false && name == false)
		{
			al_stop_sample_instance(music_muerte);
			al_stop_sample_instance(music_menu);
			al_play_sample_instance(instans);
			if (n == 1)
			{
				//////////////////////////////////////////////////////// CARGAMOS LOS NIVELES Y LOS OBJETOS DE CADA UNO VIA ARCHIVOS ////////////////////////////////////////////////////////
							
				FILE* salas[9] = { fopen(map1 , "r"),fopen(map2 , "r") ,fopen(map3, "r") ,fopen(map4 , "r") ,fopen(map5 , "r") ,fopen(map6 , "r") ,fopen(map7 , "r") ,fopen(map8 , "r") ,fopen(map9 , "r") };
				for (i = 0; i < SIZE; i++)
				{
					for (j = 0; j < SIZE; j++)
					{
						fscanf(salas[nivel_mapa], "%c", &mapa[i][j]);
					}
					fscanf(salas[nivel_mapa], "%c", &basura);
				}
				for (i = 0; i < SIZE; i++)
				{
					for (j = 0; j < SIZE; j++)
					{
						if (mapa[j][i] == 'I')
						{
							dx[contx] = i * 256;
							dy[contx] = j * 144;
							contx++;
						}
						if (mapa[j][i] == 'L')
						{
							llave_x = i * 256;
							llave_y = j * 144;
						}
					}
				}

				if (nivel_mapa >= 1)
				{
					for (k = 0; k < contx; k++)
					{
						for (i = 0; i < mini_SIZE; i++)
						{
							for (j = 0; j < mini_SIZE; j++)
							{
								if (mini_mapa[j][i] == 'T')
								{
									torretas[cont].x = i * 16 + dx[k];
									torretas[cont].y = j * 9 + dy[k];
									cont++;
								}
							}
						}
					}
				}

				for (i = 0; i < mini_SIZE; i++)
				{
					for (j = 0; j < mini_SIZE; j++)
					{
						if (item_cura[j][i] == 'C')
						{
							dx1[contx1] = i * 16 + llave_x;
							dy1[contx1] = j * 9 + llave_y;
							contx1++;
						}
					}
				}
								
				n = 0;
			}
			

			//////////////////////////////////////////////////////// DIBUJAMOS EL FONDO Y SUS ELEMENTOS ////////////////////////////////////////////////////////
		
			al_draw_scaled_bitmap(fondo, 0, 0, 1900, 1080, 0, 0, al_get_display_width(ventana), al_get_display_height(ventana), 0);
			angulo_rot_torreta(player, torretas, cont, angulo_torretas);
			

			for (i = 0; i < contx; i++)
			{
				al_draw_scaled_bitmap(isla, 0, 0, al_get_bitmap_width(isla), al_get_bitmap_height(isla), dx[i], dy[i], 256, 144, 0);
			}

			//////////////////////////////////////////////////////// DIBUJO DE LAS TORRETAS ////////////////////////////////////////////////////////
			if (nivel_mapa >= 1)
			{
				for (i = 0; i < cont; i++)
				{
					if (torretas[i].vida == 0)
					{
						al_draw_scaled_rotated_bitmap(torre, al_get_bitmap_width(torre) / 2, al_get_bitmap_height(torre) / 2, torretas[i].x, torretas[i].y, 0.15, 0.15, angulo_torretas[i], 0);

					}
					else
					{
						torretas[i].x = 0; torretas[i].y = 0;
					}
					if (nivel_mapa == 7 && torretas[i].vida == 0)
					{
						torretas[i].vida++;
						
					}

				}
			}
		
			//////////////////////////////////////////////////////// TIMER PARA CONTROLAR LOS FPS (CANTIDAD DE CICLOS POR SEGUNDO ////////////////////////////////////////////////////////

			if (Evento.type == ALLEGRO_EVENT_TIMER)
			{

				if (Evento.timer.source == fps)
				{
					fpss = fpss + 1;
				}
			}

			//////////////////////////////////////////////////////// TECLAS PARA CONTROLAR AL JUGADOR ////////////////////////////////////////////////////////
			if (Evento.type == ALLEGRO_EVENT_KEY_DOWN)
			{

				switch (Evento.keyboard.keycode)
				{
				case ALLEGRO_KEY_UP:
					freno = false;
					break;

				case ALLEGRO_KEY_DOWN:
					freno = true;
					break;

				case ALLEGRO_KEY_RIGHT:
					orientacion_jugador++;
					if (orientacion_jugador > 15)
					{
						orientacion_jugador = 0;
					}

					if (orientacion_jugador == 0 || orientacion_jugador == 8)
					{
						ajuste = orientacion_jugador;
					}
					if (orientacion_jugador == 12)
					{
						ajuste = 8;
					}
					if ((orientacion_jugador > 4 && orientacion_jugador < 8) || orientacion_jugador > 12)
					{
						ajuste = ajuste + 2;
					}


					break;

				case ALLEGRO_KEY_LEFT:
					orientacion_jugador = orientacion_jugador - 1;
					if (orientacion_jugador < 0)
					{
						orientacion_jugador = 15;
						ajuste = 16;
					}

					if (orientacion_jugador == 0 || orientacion_jugador == 8)
					{
						ajuste = orientacion_jugador;
					}
					if (orientacion_jugador == 12)
					{
						ajuste = 8;
					}
					if ((orientacion_jugador >= 4 && orientacion_jugador < 8) || orientacion_jugador > 12)
					{
						ajuste = ajuste - 2;
					}
					break;
				case ALLEGRO_KEY_Q:
					if (cambiar_pos == 0)
					{
						cambiar_pos = 1;
					}
					else
					{
						cambiar_pos = 0;
					}
					break;
				case ALLEGRO_KEY_K:
					vida_player = 5;
					break;
				case ALLEGRO_KEY_N:
					player.x = 0;
					n = 1;
					nivel_mapa++;
					num_enem = 0;
					contx = 0;
					cont = 0;
					repara = 0;
					contx1 = 0;
					llave_y = -500; llave_x = -500;
					reset_enem(enem);
					reset_disparos(disparos);
					reset_torretas(torretas);
					break;
				case ALLEGRO_KEY_D:
					inmortal = true;
				
				
				}
			}
			/*//==============     AJUSTAR VELOCIDAD PARA LAS POSICIONES    ================================//*/
			if (freno == false)
			{
				if (choque[orientacion_jugador] == 0)
				{
					player.y = player.y - player.vel_y[orientacion_jugador];
					player.x = player.x + player.vel_x[orientacion_jugador];
				}
			}

			//================== CARGAR POSICIONES DE LAS BALAS    ==============================//

			if (Evento.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				if (Evento.keyboard.keycode == ALLEGRO_KEY_SPACE)
				{
					if (cant_disparos < max_disparos_ply && reloading == false)
					{
						animacion = true;
						cantFrame_Disparo = 0;
						al_play_sample(disparo_, 2.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						cont1[cant_disparos] = orientacion_jugador;

						player.disparos_ply[cant_disparos].pos_y = player.y - 54 * cos(omega[cont1[cant_disparos]] * f);
						player.disparos_ply[cant_disparos].pos_x = player.x + 53 * sin(omega[cont1[cant_disparos]] * f);
						if (cambiar_pos == 0)
						{
							player.disparos_ply[cant_disparos].vel_x = speed_bala * cos(omega[cont1[cant_disparos]] * f);
							player.disparos_ply[cant_disparos].vel_y = speed_bala * sin(omega[cont1[cant_disparos]] * f);
							animacion_x = player.disparos_ply[cant_disparos].pos_x + 35 * cos(omega[orientacion_jugador] * f);
							animacion_y = player.disparos_ply[cant_disparos].pos_y + 35 * sin(omega[orientacion_jugador] * f);
						}
						else
						{
							player.disparos_ply[cant_disparos].vel_x = -speed_bala * cos(omega[cont1[cant_disparos]] * f);
							player.disparos_ply[cant_disparos].vel_y = -speed_bala * sin(omega[cont1[cant_disparos]] * f);
							animacion_x = player.disparos_ply[cant_disparos].pos_x - 35 * cos(omega[orientacion_jugador] * f);
							animacion_y = player.disparos_ply[cant_disparos].pos_y - 35 * sin(omega[orientacion_jugador] * f);
						}

						cant_disparos++;

						if (cant_disparos % 3 == 0)
						{
							auxx = true;
						}

					}

				}
			}
			//////////////////////////////////////////////////////// DIBUJO DE LAS BALAS ////////////////////////////////////////////////////////
			if (cant_disparos > 0)
			{
				for (i = 0; i < cant_disparos; i++)
				{
					player.disparos_ply[i].pos_x = player.disparos_ply[i].pos_x + player.disparos_ply[i].vel_x;
					player.disparos_ply[i].pos_y = player.disparos_ply[i].pos_y + player.disparos_ply[i].vel_y;
					if (player.disparos_ply[i].pos_x < 1280 && player.disparos_ply[i].pos_x > 0)
					{
						if (player.disparos_ply[i].pos_y < 720 && player.disparos_ply[i].pos_y > 0)
						{
							al_draw_bitmap(bala1[cont1[i]], player.disparos_ply[i].pos_x, player.disparos_ply[i].pos_y, 0);
						}
					}
				}
			}



			//===================    RECARGAS    ====================//

			if (cant_disparos % 3 == 0 && auxx == true)
			{
				reloading = true;
				if (Evento.type == ALLEGRO_EVENT_TIMER)
				{
					if (Evento.timer.source == recarga)
					{
						if (recarga_ < 1)
						{
							recargas = al_load_bitmap(circulo);
						}
						if (recarga_ >= 1 && recarga_ < 2)
						{
							recargas = al_load_bitmap(bala1_4);
						}
						if (recarga_ >= 2 && recarga_ < 3)
						{
							recargas = al_load_bitmap(bala2_4);
						}
						if (recarga_ >= 3 && recarga_ < 4)
						{
							recargas = al_load_bitmap(bala3_4);
						}
						if (recarga_ >= 4)
						{
							recargas = al_load_bitmap(bala_completa);
							recarga_ = -1;
							reloading = false;
							auxx = false;
							if (cant_disparos == max_disparos_ply)
							{
								cant_disparos = 0;
							}
						}
						recarga_++;
					}
				}
			}

			//////////////////////////////////////////////////////// TIMER PARA CONTROLAR LAS ANIMACIONES O FRAMES ////////////////////////////////////////////////////////
			if (Evento.type == ALLEGRO_EVENT_TIMER)
			{
				if (++cantFrame_Fuego >= 8)
				{
					cantFrame_Fuego = 0;
				}
				if (animacion == true)
				{
					if (cantFrame_Disparo < 5)
					{
						cantFrame_Disparo++;
					}
					else
					{
						animacion = false;
					}
				}
				if (++cantFrame_Humo >= 4)
				{
					cantFrame_Humo = 0;
				}
			}


			//====================    APARICION DE ENEMEGOS 1  ========================//

			//////////////////////////////////////////////////////// CREACION DE ENEMIGOS ////////////////////////////////////////////////////////
			if (timer_enem.aux == 0 && num_enem < max_enemy - 1 && nivel_mapa < 7)
			{
				num_enem++;
				enem[num_enem] = crear_enemgios(enem[num_enem], num_enem, nivel_mapa);
				timer_enem.aux = 1;
			}
			if (timer_enem.timer++ > 120)
			{
				timer_enem.aux = 0; timer_enem.timer = 0;
			}

			//////////////////////////////////////////////////////// DIBUJOS DE ENEMIGOS ////////////////////////////////////////////////////////
			if (num_enem > 0)
			{
				for (i = 1; i <= num_enem; i++)
				{

					if (enem[i].pos_y > -150)
					{
						if (enem[i].flag == 0)
						{
							enem[i].pos_y = enem[i].pos_y + enem[i].vel_y;
							enem[i].pos_x = enem[i].pos_x + enem[i].vel_x;

							al_draw_rotated_bitmap(enemy1, al_get_bitmap_width(enemy1) / 2, al_get_bitmap_height(enemy1) / 2, enem[i].pos_x, enem[i].pos_y, enem[i].angulo, 0);
							al_draw_rotated_bitmap(humo[cantFrame_Humo],63,168, enem[i].pos_x, enem[i].pos_y - 10,enem[i].angulo + 180*f, 0);

						}
						else
						{

							if (enem[i].flag != 0)
							{
								enem[i].pos_x = -1500;
								enem[i].pos_y = -1500;
								enem[i].vel_x = 0;
								enem[i].vel_y = 0;
								enem[i].ndisparos = 0;
								enem[i].flag = 1;
							}
						}
					}
					else
					{

						enem[i].pos_x = -1500;
						enem[i].pos_y = -1500;
						enem[i].vel_x = 0;
						enem[i].vel_y = 0;
						enem[i].ndisparos = 0;
						enem[i].flag = 1;


					}
				}
			}
			//================= CREACION DE LAS BALAS ENEMIGAS 1 =======================//
			if (contt++ > 30 && (enem[num_enem].flag == 0 || enem[num_enem].pos_y > -100 && enem[num_enem].pos_y < 720) && nivel_mapa < 7)
			{
				aux = 0; contt = 0;
				sonido_disparo = activar_sond_disparo(enem, num_enem, sonido_disparo);
				if (sonido_disparo = true)
				{
					al_play_sample(sonido_enem, 2, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				}
			}

			if (aux == 0)
			{

				for (j = 1; j <= num_enem; j++)
				{
					if (enem[j].ndisparos <= max_disparos)
					{
						if (enem[j].flag == 0)
						{
							enem[j].ndisparos++;
							disparos[enem[j].ndisparos] = crear_balas(disparos, enem, j, nivel_mapa);

						}
						else
						{
							reset_disparos(disparos);
						}
						if (j == num_enem)
						{
							aux = 1;

						}
					}
				}

			}
			//////////////////////////////////////////////////////// DIBUJOS DE LAS BALAS ////////////////////////////////////////////////////////

			for (i = 1; i <= max_disparos; i++)
			{

				if (disparos[i].x < 1280 && disparos[i].x > 0 && disparos[i].y < 720 && disparos[i].y > 0)
				{
					disparos[i].x = disparos[i].x + disparos[i].vel_x;
					disparos[i].y = disparos[i].y + disparos[i].vel_y;
					al_draw_rotated_bitmap(bala1[0], al_get_bitmap_width(bala1[0]) / 2, al_get_bitmap_height(bala1[0]), disparos[i].x, disparos[i].y, disparos[i].angulo, enem[i].flag);
				}
				else
				{
					disparos[i].x = 0;
					disparos[i].vel_x = 0;
					disparos[i].y = 0;
					disparos[i].vel_y = 0;
				}
			}

			//////////////////////////////////////////=====================CREACION DISPAROS DE TORRETAS ==================///////////////////////

			if (disp_misiles++ > 120 && nivel_mapa >= 1)
			{
				disp_misiles = 0; aux1 = true;
				sonido_misil1 = activar_sond_misil(torretas, cont, sonido_misil1);
				if (sonido_misil1 == true)
				{
					al_play_sample(sonido_misil, 1, 0, 2, ALLEGRO_PLAYMODE_ONCE, 0);

				}
			}



			if (aux1 == true)
			{
				for (i = 0; i < cont; i++)
				{
					misiles[i] = crear_misiles(torretas, misiles, cont, nivel_mapa, i);
					if (i == cont - 1)
					{
						aux1 = false;
					}
				}
			}

			//////////////////////////////////////////////////////// DIBUJO DE LOS MISILES ////////////////////////////////////////////////////////
			for (j = 0; j < cont; j++)
			{

				if (misiles[j].x < 1280 && misiles[j].x > 0 && misiles[j].y < 720 && misiles[j].y > 0)
				{
					misiles[j].x = misiles[j].x - misiles[j].vel_x;
					misiles[j].y = misiles[j].y - misiles[j].vel_y;

					al_draw_scaled_rotated_bitmap(misil, al_get_bitmap_width(misil) / 2, al_get_bitmap_height(misil), misiles[j].x, misiles[j].y, 0.1, 0.1, misiles[j].angulo, 0);
				}
				else
				{
					misiles[j].x = 0;
					misiles[j].vel_x = 0;
					misiles[j].y = 0;
					misiles[j].vel_y = 0;
				}

			}

			///////////////////////======================== CREACION DE JEFE(BOSS) ===================////////////////////////
			if (nivel_mapa == 7)
			{
				//////////////////////////////////////////////////////// CONFIGURACION DE SU DESPAZAMIENTO ////////////////////////////////////////////////////////
				switch (activar_cambio)
				{
				case 1:
					if (boss.pos_x >= 1280)
					{
						pos_boss = 0;
						activar_cambio = 0;
						boss = moviento_jefe(boss, pos_boss);
					}
					break;
				case 2:
					if (boss.pos_y <= player.y)
					{
						boss.pos_x = player.x;
					}
					if (boss.pos_y >= 720)
					{
						pos_boss = 2;
						activar_cambio = 1;
						boss = moviento_jefe(boss, pos_boss);
					}
					break;
				case 0:
					if (boss.pos_x >= player.x)
					{
						boss.pos_y = player.y;
					}
					if (boss.pos_x <= 0)
					{
						pos_boss = 1;
						activar_cambio = 2;
						boss = moviento_jefe(boss, pos_boss);
					}
					break;
				}	
				boss.pos_x = boss.pos_x + boss.vel_x;
				boss.pos_y = boss.pos_y + boss.vel_y;

				//////////////////////////////////////////////////////// CREACION DE LOS DISPAROS DEL BOSS ////////////////////////////////////////////////////////
				if (++tiempo_disp_boss > 10)
				{
					disp_boss = 1;
					tiempo_disp_boss = 0;
				}

				if (disp_boss == 1)
				{

					if (boss.ndisparos <= 1000)
					{
						al_play_sample(ametralladora, 1, 0, 1.5, ALLEGRO_PLAYMODE_ONCE, 0);
						if (boss.vida != 7)
						{
							if (activar_cambio == 0)
							{

								boss.ndisparos++;
								disparos_boss[boss.ndisparos].x = boss.pos_x - 33;
								disparos_boss[boss.ndisparos].y = boss.pos_y - 75;
								disparos_boss[boss.ndisparos].vel_x = -speed_bala;
								disparos_boss[boss.ndisparos].vel_y = 0;

								boss.ndisparos++;
								disparos_boss[boss.ndisparos].x = boss.pos_x - 33;
								disparos_boss[boss.ndisparos].y = boss.pos_y + 75;
								disparos_boss[boss.ndisparos].vel_x = -speed_bala;
								disparos_boss[boss.ndisparos].vel_y = 0;

								disp_boss = 0;
							}
							if (activar_cambio == 2)
							{
								boss.ndisparos++;
								disparos_boss[boss.ndisparos].x = boss.pos_x - 75;
								disparos_boss[boss.ndisparos].y = boss.pos_y + 33;
								disparos_boss[boss.ndisparos].vel_x = 0;
								disparos_boss[boss.ndisparos].vel_y = speed_bala;

								boss.ndisparos++;
								disparos_boss[boss.ndisparos].x = boss.pos_x + 75;
								disparos_boss[boss.ndisparos].y = boss.pos_y + 33;
								disparos_boss[boss.ndisparos].vel_x = 0;
								disparos_boss[boss.ndisparos].vel_y = speed_bala;

								disp_boss = 0;
							}
						}
					}
				}
				//////////////////////////////////////////////////////// DIBUJO DE LAS BALAS ////////////////////////////////////////////////////////
				for (i = 0; i <= max_disparos; i++)
				{
					disparos_boss[i].x = disparos_boss[i].x + disparos_boss[i].vel_x;
					disparos_boss[i].y = disparos_boss[i].y + disparos_boss[i].vel_y;
					al_draw_bitmap(bala1[0], disparos[i].x, disparos[i].y, 0);
					if (disparos_boss[i].x < 1280 && disparos_boss[i].x > 0 && disparos_boss[i].y < 720 && disparos_boss[i].y > 0)
					{
						disparos_boss[i].x = disparos_boss[i].x + disparos_boss[i].vel_x;
						disparos_boss[i].y = disparos_boss[i].y + disparos_boss[i].vel_y;
						al_draw_bitmap(bala1[0], disparos_boss[i].x, disparos_boss[i].y, 0);
					}

				}

				//////////////////////////////////////////////////////// COLISION DE LAS BALAS DEL JUGADOR CON EL BOSS////////////////////////////////////////////////////////
				col_bala_boss(player, boss, cant_disparos, nivel_mapa, &i, &activar_col5);
				if(activar_col5 == 1)
				{
					if (boss.vida < 8)
					{
						boss.vida++;
					}
					else
					{
						puntajes = puntajes + 5000;
					}
					player.disparos_ply[i].pos_y = 2000;
					player.disparos_ply[i].pos_x = 2000;
					player.disparos_ply[i].vel_x = 0;
					player.disparos_ply[i].vel_y = 0;

				}
			}














			//==================   COLISION BALA-----ENEMIGO   =================//
			col_bala_enemigo(player, enem, num_enem, cant_disparos, disparos_ply, &i, &k, &activar_col1,boss,nivel_mapa);
			if (activar_col1 == 1)
			{
				enem[k].vida++;
				if (enem[k].vida >= 3)
				{
					enem[k].flag = 1;
				}
				player.disparos_ply[i].pos_y = 2000;
				player.disparos_ply[i].pos_x = 2000;
				player.disparos_ply[i].vel_x = 0;
				player.disparos_ply[i].vel_y = 0;
				puntajes = puntajes + 100 * rachas_;
				if (rachas_ < 6)
				{
					rachas_++;
				}
			}
			///////////////////////////================ COLISION ITEM PARA CURAR Y JUGADOR =============//////////////////
			angulo_x = 100 * sin(omega[orientacion_jugador] * f);
			angulo_y = 100 * cos(omega[orientacion_jugador] * f);
			if (mapa[(player.y - angulo_y) / 144][(player.x + angulo_x) / 256] == 'L')
			{

				for (k = 0; k < contx; k++)
				{
					if (item_cura[(player.y - angulo_y - dy[k]) / 9][(player.x + angulo_x - dx[k]) / 16] == 'C' && repara == 0)
					{
						al_play_sample(reparacion, 5, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
						vida_player = 0;
						repara = 1;

					}
				}
			}
			if (repara == 0)
			{
				al_draw_bitmap(llave, llave_x, llave_y, repara);
			}


			////////////////////////////////////////////////================= COLISION BALA ------ PLAYER ==================//////////////////////////////////////////////////////



			col_bala_jugador(player, disparos, omega, orientacion_jugador, col_jug_enem, ajuste, &activar_col2, &i,disparos_boss);
			if (activar_col2 == 1)
			{
				if (vida_player < 5)
				{
					vida_player++;
				}
				disparos[i].x = 2000;
				if (nivel_mapa == 7)
				{
					disparos_boss[i].x = 0;
					disparos[i].vel_x = 0;
				}
			}

			////////////////////////////////////////////////================= COLISION MISIL ------ PLAYER ==================//////////////////////////////////////////////////////
			col_misil_jugador(player, misiles, omega, orientacion_jugador, col_jug_enem, cont, ajuste, &activar_col4, &i);
			if (activar_col4 == 1)
			{
				if (vida_player < 4)
				{
					vida_player++;
					vida_player++;
				}
				else if (vida_player < 5)
				{
					vida_player++;
				}
				misiles[i].x = 2000;
			}

			//==================== COLISION JUGADOR-----ENEMIGOS   ======================//


			col_enem_jugador(player, enem, omega, orientacion_jugador, num_enem, ajuste, col_jug_enem, &activar_col3, &i);
			if (activar_col3 == 1)
			{
				enem[i].flag = 1;
				if (vida_player < 4)
				{
					vida_player++;
					vida_player++;
				}
				else if (vida_player < 5)
				{
					vida_player++;
				}
			}
			////////////////////////////////////////////////================= BALAS PLAYER ------ TORRETAS ==================//////////////////////////////////////////////////////


			if (cant_disparos > 0 && nivel_mapa >= 1)
			{
				for (i = 0; i <= cant_disparos; i++)
				{
					if ((player.disparos_ply[i].pos_y) / 144 >= 0 && (player.disparos_ply[i].pos_x) / 256 >= 0)
					{
						if (mapa[(player.disparos_ply[i].pos_y) / 144][(player.disparos_ply[i].pos_x) / 256] == 'I')
						{
							for (k = 0; k < contx; k++)
							{
								if (torretas[k].vida == 0)
								{

									if (mini_mapa[(player.disparos_ply[i].pos_y - dy[k]) / 9][(player.disparos_ply[i].pos_x - dx[k]) / 16] == 'e')
									{
										torretas[k].vida++;
										puntajes = puntajes + 500;
										player.disparos_ply[i].pos_y = 0;
										player.disparos_ply[i].pos_x = 0;
										player.disparos_ply[i].vel_x = 0;
										player.disparos_ply[i].vel_y = 0;



									}
									if (mini_mapa[(player.disparos_ply[i].pos_y - dy[k]) / 9][(player.disparos_ply[i].pos_x - dx[k]) / 16] == 'T')
									{
										torretas[k].vida++;
										puntajes = puntajes + 500;
										player.disparos_ply[i].pos_y = 0;
										player.disparos_ply[i].pos_x = 0;
										player.disparos_ply[i].vel_x = 0;
										player.disparos_ply[i].vel_y = 0;

									}
								}
							}
						}
					}
				}
			}




			//////////////////////====================== COLISION CON LA LOS LIMITES DE LA VENTANA ===============================//////////////////////


			col_ventana(player, &choque_vent, angulo_y, angulo_x);
			if (cambio_nivel == false)
			{
				if (choque_vent == 0)
				{
					choque[orientacion_jugador] = 0;
				}
				else
				{
					if (choque_vent == 0)
					{
						choque[orientacion_jugador] = 0;
					}
					else
					{
						choque[orientacion_jugador] = 1;
					}
				}
			}

			//////////////////////////////////////////////////////// COLISION CON LAS ISLAS VIA ARCHIVOS ////////////////////////////////////////////////////////

			if (mapa[(player.y - angulo_y) / 144][(player.x + angulo_x) / 256] == 'I')
			{
				for (k = 0; k < contx; k++)
				{
					if (mini_mapa[(player.y - angulo_y - dy[k]) / 9][(player.x + angulo_x - dx[k]) / 16] == 'x')
					{
						choque[orientacion_jugador] = 0;
					}
					if (mini_mapa[(player.y - angulo_y - dy[k]) / 9][(player.x + angulo_x - dx[k]) / 16] == 'C')
					{
						choque[orientacion_jugador] = 1;
					}
				}
			}
		


			///////////////////////////========================= CAMBIO DE NIVELES ===============================////////////////////////////////////////////////
			if(enem[max_enemy - 1].flag != 0 || enem[max_enemy - 1].pos_y < -100 || enem[max_enemy - 1].pos_y > 820 || enem[max_enemy - 1].pos_x < -100 || enem[max_enemy - 1].pos_x > 1380)//(enem[max_enemy - 1].flag != 0 || enem[max_enemy - 1].pos_y < -100 || enem[max_enemy - 1].pos_y > 820 || enem[max_enemy - 1].pos_x < -
			{
				cambio_nivel = true;
				switch (nivel_mapa)
				{
				case 0:
					al_draw_scaled_rotated_bitmap(flechas, al_get_bitmap_width(flechas) / 2, al_get_bitmap_height(flechas) / 2, 1200, 360, 0.2, 0.2, 90 * f, 0);
					if (player.x > 1280)
					{
						player.x = 0;
						nivel_mapa++;

						reset_general(&n, &llave_x, &llave_y, &num_enem, &contx, &cont, &repara, &contx1);
						reset_enem(enem);
						reset_disparos(disparos);
						reset_torretas(torretas);
					}
					break;
				case 1:
					al_draw_scaled_rotated_bitmap(flechas, al_get_bitmap_width(flechas) / 2, al_get_bitmap_height(flechas) / 2, 640, 600, 0.2, 0.2, 180 * f, 0);
					if (player.y > 720)
					{
						player.y = 0;
						nivel_mapa++;
						reset_general(&n, &llave_x, &llave_y, &num_enem, &contx, &cont, &repara, &contx1);
						reset_enem(enem);
						reset_disparos(disparos);
						reset_torretas(torretas);


					}
					break;

				case 2:

					al_draw_scaled_rotated_bitmap(flechas, al_get_bitmap_width(flechas) / 2, al_get_bitmap_height(flechas) / 2, 640, 600, 0.2, 0.2, 180 * f, 0);
					if (player.y > 720)
					{
						player.y = 0;
						nivel_mapa++;
						reset_general(&n, &llave_x, &llave_y, &num_enem, &contx, &cont, &repara, &contx1);
						reset_enem(enem);
						reset_disparos(disparos);
						reset_torretas(torretas);
					}
					break;

				case 3:
					al_draw_scaled_rotated_bitmap(flechas, al_get_bitmap_width(flechas) / 2, al_get_bitmap_height(flechas) / 2, 80, 360, 0.2, 0.2, -90 * f, 0);
					if (player.x < 0)
					{
						player.x = 1280;
						nivel_mapa++;
						reset_general(&n, &llave_x, &llave_y, &num_enem, &contx, &cont, &repara, &contx1);
						reset_enem(enem);
						reset_disparos(disparos);
						reset_torretas(torretas);
					}
					break;


				case 4:
					al_draw_scaled_rotated_bitmap(flechas, al_get_bitmap_width(flechas) / 2, al_get_bitmap_height(flechas) / 2, 80, 360, 0.2, 0.2, -90 * f, 0);
					al_draw_scaled_rotated_bitmap(flechas, al_get_bitmap_width(flechas) / 2, al_get_bitmap_height(flechas) / 2, 640, 80, 0.2, 0.2, 0, 0);
					if (player.x < 0 || player.y < 0)
					{
						if (player.x < 0)
						{
							player.x = 1280;
						}
						else if (player.y < 0)
						{
							player.y = 720;
						}
						nivel_mapa++;
						reset_general(&n, &llave_x, &llave_y, &num_enem, &contx, &cont, &repara, &contx1);
						reset_enem(enem);
						reset_disparos(disparos);
						reset_torretas(torretas);
					}
					break;
				case 5:
					al_draw_scaled_rotated_bitmap(flechas, al_get_bitmap_width(flechas) / 2, al_get_bitmap_height(flechas) / 2, 640, 80, 0.2, 0.2, 0, 0);
					if (player.y < 0)
					{
						player.y = 720;
						nivel_mapa++;
						reset_general(&n, &llave_x, &llave_y, &num_enem, &contx, &cont, &repara, &contx1);
						reset_enem(enem);
						reset_disparos(disparos);
						reset_torretas(torretas);
						
					}
					break;
				case 6:
					al_draw_scaled_rotated_bitmap(flechas, al_get_bitmap_width(flechas) / 2, al_get_bitmap_height(flechas) / 2, 640, 80, 0.2, 0.2, 0, 0);
					if (player.y < 0)
					{
						player.y = 720;
						nivel_mapa++;
						reset_general(&n, &llave_x, &llave_y, &num_enem, &contx, &cont, &repara, &contx1);
						num_enem = max_enemy;
						reset_enem(enem);
						reset_disparos(disparos);
						reset_torretas(torretas);
						break;
					}
				}
			}
			else
			{
			cambio_nivel = false;
			}


			///////////////////======================= ACTIVAR LINEAS GUIA ========================///////////////////////

			if (Evento.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				if (Evento.keyboard.keycode == ALLEGRO_KEY_1)
				{
					lineas_guia = true;
				}
			}
			if (Evento.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				if (Evento.keyboard.keycode == ALLEGRO_KEY_2)
				{
					lineas_guia = false;
				}
			}
			if (lineas_guia == true)
			{
				al_draw_rectangle(boss.pos_x + 108, boss.pos_y + 108, boss.pos_x - 108, boss.pos_y - 108, negro, 5);
				al_draw_rectangle((player.x + 100 * sin(col_jug_enem[orientacion_jugador - ajuste] * f)) + error_x_jugador(omega, orientacion_jugador), (player.y + 100 * cos(col_jug_enem[orientacion_jugador - ajuste] * f)) + error_y_jugador(omega, orientacion_jugador), (player.x - 100 * sin(col_jug_enem[orientacion_jugador - ajuste] * f)) - error_x_jugador(omega, orientacion_jugador), (player.y - 100 * cos(col_jug_enem[orientacion_jugador - ajuste] * f)) - error_y_jugador(omega, orientacion_jugador), negro, 5);
				for (i = 0; i < cont; i++)
				{
					if (torretas[i].vida == 0)
					{
						al_draw_line(player.x, player.y, torretas[i].x, torretas[i].y, rojo, 5);
						al_draw_line(player.x, player.y, torretas[i].x, torretas[i].y, blanco, 2);
					}
					else
					{
						torretas[i].x = 0; torretas[i].y = 0;
					}
				}

				for (i = 1; i <= num_enem; i++)
				{

					if (enem[i].angulo != 270* f)
					{
						al_draw_rectangle(enem[i].pos_x + 20 - 75 * sin(enem[i].angulo), enem[i].pos_y - 75 * cos(enem[i].angulo), enem[i].pos_x - 20 + 75 * sin(enem[i].angulo), enem[i].pos_y + 75 * cos(enem[i].angulo), negro, 5);
					}
					if(nivel_mapa == 2)
					{
						al_draw_rectangle(enem[i].pos_x - 75, enem[i].pos_y + 20, enem[i].pos_x + 75, enem[i].pos_y - 20, negro, 5);
					}
				}
			}

			
			///////////////////////////////////////////////// DIBUJOS GENERALES DEL JUEGO /////////////////////////////////////////////////

			al_draw_rotated_bitmap(jugador[cambiar_pos], 100, 100, player.x, player.y, omega[orientacion_jugador] * f, 0);
			if (nivel_mapa == 7 && boss.vida != 7)
			{
				al_draw_rotated_bitmap(avion, al_get_bitmap_width(avion) / 2, al_get_bitmap_height(avion) / 2, boss.pos_x, boss.pos_y, boss.angulo, 0);

			}
			al_draw_bitmap(circulo_, 1100, 600, 0);
			al_draw_bitmap(recargas, 1100, 600, 0);
			if (animacion == true)
			{
				al_draw_scaled_rotated_bitmap(disparos_[cantFrame_Disparo], al_get_bitmap_width(disparos_[cantFrame_Disparo]) / 2, al_get_bitmap_height(disparos_[cantFrame_Disparo]) / 2, animacion_x, animacion_y, 0.2, 0.2, omega[orientacion_jugador] * f, 0);
			}
			if (vida_player >= 2)
			{
				al_draw_scaled_rotated_bitmap(fuegos_[cantFrame_Fuego], al_get_bitmap_width(fuegos_[cantFrame_Fuego]) / 2, al_get_bitmap_height(fuegos_[cantFrame_Fuego]), player.x + 40 * sin(omega[orientacion_jugador] * f), player.y + 20 - 40 * cos(omega[orientacion_jugador] * f), 0.2, 0.2, 0, 0);
			}
			if (vida_player >= 4)
			{
				al_draw_scaled_rotated_bitmap(fuegos_[cantFrame_Fuego], al_get_bitmap_width(fuegos_[cantFrame_Fuego]) / 2, al_get_bitmap_height(fuegos_[cantFrame_Fuego]), player.x - 40 * sin(omega[orientacion_jugador] * f), player.y + 30 + 30 * cos(omega[orientacion_jugador] * f), 0.2, 0.2, 0, 0);
			}
			al_draw_scaled_bitmap(tabla_puntajes, 0, 0, al_get_bitmap_width(tabla_puntajes), al_get_bitmap_height(tabla_puntajes), 900, 0, 2 * al_get_bitmap_width(tabla_puntajes) / 3, 2 * al_get_bitmap_height(tabla_puntajes) / 3, 0);
			al_draw_scaled_bitmap(racha, 0, 0, al_get_bitmap_width(racha), al_get_bitmap_height(racha), 1025, 58, 2 * al_get_bitmap_width(racha) / 3, 2 * al_get_bitmap_height(racha) / 3, 0);
			al_draw_textf(letra, negro, 940, 20, 0, "Puntaje: %d", puntajes);
			al_draw_textf(letra1, negro, 1035, 60, 0, "Racha: x%d", rachas_);
			al_draw_textf(letra2, negro, 10, 10, 0, "Nivel: %d", nivel_mapa + 1);
			al_draw_scaled_bitmap(vida[vida_player], 0, 0, al_get_bitmap_width(vida[vida_player]), al_get_bitmap_height(vida[vida_player]), 700, 10, 2 * al_get_bitmap_width(vida[vida_player]) / 3, 2 * al_get_bitmap_height(vida[vida_player]) / 3, 0);

			///////////////////////////////////////////////// BANDERA PARA ACTIVAR LA PANTALLA DE MUERTE /////////////////////////////////////////////////
			if (vida_player == 5 && inmortal == false)
			{
				muerte = true;
				grabar = 0;
			}

			///////////////////////////////////////////////// CICLO PARA LA VICTORIA
			while (boss.vida >= 7)
			{
				if (boss.vida >= 7)
				{
					play = false;
					al_wait_for_event(cola2, &Evento2);
					al_start_timer(seg);
					al_pause_event_queue(cola, true);
					al_draw_rotated_bitmap(winer, al_get_bitmap_width(winer) / 2, al_get_bitmap_height(winer) / 2, 1280 / 2, 720 / 2 - 100, 0, 0);
					if (Evento2.type == ALLEGRO_EVENT_TIMER)
					{
						if (Evento2.timer.source == seg)
						{
							segundo++;


						}
					}
					if (segundo >= 3)
					{
						///////////////////////////////////////////////// RESETEOS GENERALES /////////////////////////////////////////////////
						for (i = 0; i < cadena; i++)
						{
							nombre[i] = nombre[i] - nombre[i];
						}
						muerte = false;
						play = false;
						instruccion = false;
						score = false;
						name = false;
						vida_player = 0;
						boss.vida = 0;
						al_pause_event_queue(cola, false);
						al_pause_event_queue(cola2, true);
						player.x = 600;
						player.y = 600;
						n = 1;
						cadena = 0;
						orientacion_jugador = 0;
						nivel_mapa = 0;
						num_enem = 0;
						puntajes = 0;
						rachas_ = 0;
						contx = 0;
						cont = 0;
						repara = 0;
						contx1 = 0;
						reset_enem(enem);
						reset_disparos(disparos);
						reset_torretas(torretas);
						for (k = 0; k <= 15; k++)
						{
							player.vel_y[k] = (speed * cos(omega[k] * f));
							player.vel_x[k] = (speed * sin(omega[k] * f));
						}
					}
				}
				al_flip_display();
			}
			if (Evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				al_destroy_bitmap(jugador[1]);
				al_destroy_bitmap(circulo_);
				return 0;
			}
			

			al_flip_display();
		}
			
		///////////////////////////////////////////////// CICLO PARA LA PANTALLA DE MUERTE /////////////////////////////////////////////////
		while (muerte == true)
		{
			al_pause_event_queue(cola, true);
			if (muerte == true)
			{
				al_play_sample_instance(music_muerte);
				al_stop_sample_instance(instans);
				al_draw_scaled_rotated_bitmap(game_over[cambio], al_get_bitmap_width(game_over[cambio]) / 2, al_get_bitmap_height(game_over[cambio]) / 2, al_get_display_width(ventana) / 2, al_get_display_height(ventana) / 2, 0.8, 0.8, 0, 0);
				al_stop_sample_instance(instans);
				al_pause_event_queue(cola2, false);
				al_wait_for_event(cola2, &Evento2);
				
				if (Evento2.type == ALLEGRO_EVENT_MOUSE_AXES || Evento2.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
				{
					cambio = 0;
					x1 = Evento2.mouse.x;
					y1 = Evento2.mouse.y;
					if (x1 >= 446 && x1 <= 617)
					{
						if (y1 >= 584 && y1 <= 663)
						{
							cambio = 1;
							if (Evento2.mouse.button)
							{
								muerte = false;
								vida_player = 0;
								al_pause_event_queue(cola, false);
								player.x = 600;
								player.y = 600;
								n = 1;
								nivel_mapa = 0;
								num_enem = 0;
								puntajes = 0;
								rachas_ = 0;
								contx = 0;
								cont = 0;
								repara = 0;
								contx1 = 0;
								orientacion_jugador = 0;
								llave_y = -500; llave_x = -500;
								reset_enem(enem);
								reset_disparos(disparos);
								reset_torretas(torretas);
								for (k = 0; k <= 15; k++)
								{
									player.vel_y[k] = (speed * cos(omega[k] * f));
									player.vel_x[k] = (speed * sin(omega[k] * f));
								}
							}
						}
					}
					if (x1 >= 702 && x1 <= 820)
					{
						if (y1 >= 584 && y1 <= 663)
						{
							cambio = 2;
							if (Evento2.mouse.button)
							{
								for (i = 0; i < cadena; i++)
								{
									nombre[i] = nombre[i]- nombre[i];
								}
								muerte = false;
								play = false;
								instruccion = false;
								score = false;
								name = false;
								vida_player = 0;
								al_pause_event_queue(cola, false);
								al_pause_event_queue(cola2, true);
								player.x = 600;
								player.y = 600;
								n = 1;
								cadena = 0;
								orientacion_jugador = 0;
								nivel_mapa = 0;
								num_enem = 0;
								puntajes = 0;
								rachas_ = 0;
								contx = 0;
								cont = 0;
								repara = 0;
								contx1 = 0;
								reset_enem(enem);
								reset_disparos(disparos);
								reset_torretas(torretas);
								for (k = 0; k <= 15; k++)
								{
									player.vel_y[k] = (speed * cos(omega[k] * f));
									player.vel_x[k] = (speed * sin(omega[k] * f));
								}
							
							}

						}
					}

				}
			}
			al_flip_display();
			///////////////////////////////////////////////// GRABAR EL PUNTAJE Y EL NOMBRE DEL JUGADOR EN EL ARCHIBO PARA EL RANKING /////////////////////////////////////////////////
			if (grabar == 0)
			{
				leeranking(ranking, &indice);
				ordenar_ranking(ranking, indice, puntajes, nombre);
				muestraranking(ranking, indice);
				grabaranking(ranking, indice);
				grabar = 1;
			}
		}
		
	}
}














