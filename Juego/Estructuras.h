struct bala_
{
	int x;
	int y;
	int vel_x;
	int vel_y;
	float angulo;
}disparos[max_disparos];

struct enemy_
{
	int vida = 0;
	int pos_x;
	int pos_y;
	int vel_x;
	int vel_y;
	int ndisparos = 0;
	int flag = 0;
	float angulo = 0;
}enem[max_enemy];



struct enemy_timer
{
	int aux = 0;
	int timer = 0;
}timer_enem;



struct bala_player
{
	int pos_x;
	int pos_y;
	int vel_x;
	int vel_y;
}disparos_ply[max_disparos_ply];

struct jugador
{
	int x = 600;
	int y = 600;
	float vel_x[16];
	float vel_y[16];
	int vida = 0;
	struct bala_player disparos_ply[max_disparos_ply];
}player;


struct jefe
{
	int vida = 0;
	int pos_x = 1380;
	int pos_y;
	int vel_x;
	int vel_y;
	float angulo;
	int ndisparos = 1;

}boss;




struct balas_boss
{
	int x;
	int y;
	int vel_x;
	int vel_y;
}disparos_boss[max_disparos];


struct salas_
{
	struct enemy_ enem[max_enemy];
	int posiciones_mapa[4];
	int id;

}salasl[9];

struct enemy2
{
	int x;
	int y;
	int ndisparos;
	int vida = 0;
}torretas[max_enemy];

struct misil
{
	int x;
	int y;
	float vel_x;
	float vel_y;
	float angulo;
}misiles[50];

struct rank
{
	char nombre[10];
	int puntaje;
};
struct rank ranking[6];



