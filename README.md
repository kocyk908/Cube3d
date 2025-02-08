# Cube3d

# Główne zmiany 08.02
✅ Główne poprawki w kodzie
1️⃣ Usunięcie angle i fov – zastąpienie ich dir_x, dir_y, plane_x, plane_y
Problem: player->angle był używany do obrotu i korekcji efektu rybiego oka, co powodowało błędy.
Rozwiązanie: Usunęliśmy angle, a do obrotu i raycastingu używamy teraz dir_x, dir_y, plane_x, plane_y.
Zaleta: Lepsza precyzja raycastingu, poprawiona obsługa obrotu, brak błędów przy ruchu.
🔹 Usunięto:

game->player.angle = 0;
game->player.fov = PI/3;
🔹 Zamieniono na:

game->player.dir_x = 1;
game->player.dir_y = 0;
game->player.plane_x = 0;
game->player.plane_y = 0.66;
2️⃣ Poprawiona funkcja set_angle() – dynamiczne ustawianie kierunku gracza
Problem: set_angle() ustawiało angle, ale nie wpływało na dir_x, dir_y, plane_x, plane_y.
Rozwiązanie: Teraz set_angle() ustawia prawidłowy kierunek i pole widzenia w zależności od pozycji gracza.
🔹 Poprawiona wersja set_angle():

void set_angle(t_game *game)
{
    if (game->player.NSWE == 'N')
    {
        game->player.dir_x = 0;
        game->player.dir_y = -1;
        game->player.plane_x = 0.66;
        game->player.plane_y = 0;
    }
    else if (game->player.NSWE == 'S')
    {
        game->player.dir_x = 0;
        game->player.dir_y = 1;
        game->player.plane_x = -0.66;
        game->player.plane_y = 0;
    }
    else if (game->player.NSWE == 'E')
    {
        game->player.dir_x = 1;
        game->player.dir_y = 0;
        game->player.plane_x = 0;
        game->player.plane_y = 0.66;
    }
    else if (game->player.NSWE == 'W')
    {
        game->player.dir_x = -1;
        game->player.dir_y = 0;
        game->player.plane_x = 0;
        game->player.plane_y = -0.66;
    }
}
3️⃣ Poprawiona obsługa obrotu kamery (move_player())
Problem: move_player() używało angle, ale nie aktualizowało dir_x, dir_y, plane_x, plane_y.
Rozwiązanie: Teraz obrót poprawnie wpływa na kierunek gracza i kamerę.
🔹 Poprawiona obsługa obrotu w move_player():

if (game->player.left_rotate)
{
    double oldDirX = game->player.dir_x;
    game->player.dir_x = game->player.dir_x * cos(angle_speed) - game->player.dir_y * sin(angle_speed);
    game->player.dir_y = oldDirX * sin(angle_speed) + game->player.dir_y * cos(angle_speed);

    double oldPlaneX = game->player.plane_x;
    game->player.plane_x = game->player.plane_x * cos(angle_speed) - game->player.plane_y * sin(angle_speed);
    game->player.plane_y = oldPlaneX * sin(angle_speed) + game->player.plane_y * cos(angle_speed);
}
4️⃣ Usunięcie efektu rybiego oka
Problem: Raycasting miał błędną korekcję efektu rybiego oka, przez co ściany były zniekształcone.
Rozwiązanie: Usunięto błędną korekcję i zastąpiono ją prawidłowym obliczeniem dystansu.
🔹 Usunięto błędne poprawki:

ray->perp_wall_dist *= cos(player->angle - atan2(ray->dir_y, ray->dir_x));
🔹 Poprawiona funkcja fixed_dist():

double fixed_dist(double x1, double y1, double x2, double y2, t_game *game)
{
    double delta_x = x2 - x1;
    double delta_y = y2 - y1;

    double ray_angle = atan2(delta_y, delta_x);
    double player_angle = atan2(game->player.dir_y, game->player.dir_x);

    double corrected_angle = ray_angle - player_angle;
    double fixed_dist = sqrt(delta_x * delta_x + delta_y * delta_y) * cos(corrected_angle);

    return fixed_dist;
}
5️⃣ Poprawiona obsługa raycastingu (draw_loop() i draw_line())
Problem: draw_loop() używało angle i fov, co powodowało problemy ze skalowaniem ścian.
Rozwiązanie: Teraz draw_loop() używa poprawnie camera_x, dir_x i plane_x.
🔹 Poprawiona wersja draw_loop():

int draw_loop(t_game *game)
{
    t_player *player = &game->player;
    move_player(game);
    clear_image(game);

    int i = 0;
    while (i < WIDTH)
    {
        double camera_x = 2 * i / (double)WIDTH - 1; // Od -1 (lewa strona) do 1 (prawa strona)
        draw_line(player, game, camera_x, i);
        i++;
    }

    mlx_put_image_to_window(game->window.mlx_ptr, game->window.win_ptr, game->window.img, 0, 0);
    return (0);
}
🚀 Podsumowanie zmian
✅ Usunięto angle i fov, zastępując je dir_x, dir_y, plane_x, plane_y
✅ Poprawiona obsługa obrotu kamery – teraz plane_x wpływa na FOV
✅ Naprawiony efekt rybiego oka – ściany są teraz poprawnie wyświetlane
✅ Poprawiona obsługa raycastingu (draw_loop()) – rysowanie promieni działa poprawnie

🔧 Co jeszcze można dodać?
🎯 Możliwość zmiany FOV w czasie rzeczywistym (zmieniając plane_x, np. plane_x = 1.0 dla FOV 90°).
🎯 Lepsza obsługa kolizji i płynniejsze sterowanie graczem.
🎯 Dodanie minimapy pokazującej promienie raycastingu.


# wyjaśnienie zmiany fov na plane_x/_y

📌 Dogłębne wyjaśnienie plane_x i plane_y w raycastingu
plane_x i plane_y określają płaszczyznę kamery, czyli jak szeroko gracz widzi świat w raycastingu.
To one kontrolują pole widzenia (FOV) i rozstawienie promieni w raycastingu.

🎯 1. Co robią plane_x i plane_y?
🔹 dir_x, dir_y określają kierunek patrzenia gracza (gdzie "środek ekranu" jest skierowany).
🔹 plane_x, plane_y określają jak szeroko rozciąga się kamera, co wpływa na FOV (pole widzenia).

📌 Ważne! plane_x i plane_y są zawsze prostopadłe do dir_x i dir_y.

📌 Wizualizacja dir_x, dir_y oraz plane_x, plane_y
Przyjmijmy, że gracz patrzy na wschód (E → dir_x = 1, dir_y = 0):

           plane_x, plane_y
                 ↖ ↑ ↗
                  \|/
                   | dir_x, dir_y (gracz patrzy tu)
------------------->

       Lewa krawędź FOV       Prawa krawędź FOV
📌 plane_x i plane_y rozciągają promienie raycastingu na boki, tworząc efekt FOV.
Jeśli plane_x = 0.66, to mamy FOV ≈ 66°
Jeśli plane_x = 1.0, to mamy FOV ≈ 90°

🎯 2. Jak plane_x i plane_y wpływają na pole widzenia (FOV)?
📌 FOV zależy od długości plane_x i plane_y.
Jeśli zwiększymy wartość plane_x, to kąt widzenia się poszerzy.
Jeśli zmniejszymy plane_x, to gracz będzie widział węższy obraz.

🔹 Standardowe wartości plane_x, plane_y:

FOV	plane_x
66°	0.66 (standard w Wolfenstein 3D)
90°	1.0 (klasyczne FPP)
120°	1.5 (szeroki ekran)
🎯 3. Jak plane_x i plane_y są ustawiane w zależności od kierunku gracza?
Jeśli gracz patrzy w jednym z czterech głównych kierunków, to wartości plane_x i plane_y zmieniają się tak, by były prostopadłe do dir_x, dir_y.

📌 Przykłady ustawień dir_x, dir_y, plane_x, plane_y:

Kierunek gracza	dir_x	dir_y	plane_x	plane_y	Opis
Patrzy na północ (N)	0	-1	0.66	0	Kamera rozszerza się w poziomie
Patrzy na południe (S)	0	1	-0.66	0	Kamera rozszerza się w poziomie
Patrzy na wschód (E)	1	0	0	0.66	Kamera rozszerza się w pionie
Patrzy na zachód (W)	-1	0	0	-0.66	Kamera rozszerza się w pionie
📌 Zawsze plane_x, plane_y są prostopadłe do dir_x, dir_y.

🎯 4. Jak plane_x i plane_y są wykorzystywane w raycastingu?
📌 plane_x i plane_y służą do rozciągania promieni w raycastingu.

Każdy promień ekranu ma swoją wartość camera_x:

double camera_x = 2 * i / (double)WIDTH - 1; // Od -1 (lewa strona) do 1 (prawa strona)
✔ Na podstawie camera_x obliczamy promień (ray_dir_x, ray_dir_y):

ray_dir_x = dir_x + plane_x * camera_x;
ray_dir_y = dir_y + plane_y * camera_x;
✔ Teraz ray_dir_x, ray_dir_y są używane do obliczenia kolizji raycastingu.

📌 Co to oznacza?

Gdy camera_x = -1 → lewa krawędź ekranu (FOV)
Gdy camera_x = 0 → środek ekranu
Gdy camera_x = 1 → prawa krawędź ekranu
💡 Dzięki plane_x i plane_y, promienie są rozciągnięte poprawnie na całą szerokość ekranu!

📌 Podsumowanie
Element	Opis
dir_x, dir_y	Określa kierunek, w którym patrzy gracz
plane_x, plane_y	Określa rozstawienie kamery (FOV)
plane_x, plane_y	Są prostopadłe do dir_x, dir_y
camera_x	Rozciąga promienie od -1 (lewo) do 1 (prawo)
ray_dir_x = dir_x + plane_x * camera_x	Oblicza rzeczywisty promień
Zwiększenie plane_x	Poszerza pole widzenia (FOV)
Zmniejszenie plane_x	Zwęża pole widzenia (FOV)
🚀 Co teraz?
✅ Teraz rozumiesz, jak plane_x i plane_y wpływają na raycasting!
✅ Jeśli masz problem z FOV, wystarczy dostosować plane_x!
✅ Jeśli chcesz zobaczyć różnice, spróbuj zmienić plane_x = 1.0 i zobacz, jak szerokie jest FOV!


## 20.11

Dodałem moje zczytywanie mapy

*map->data ->>>>> map->board

Zczytywanie szerokości narazie zostawiłem jako mapę kwadratową ale bedzie trzeba to chyba zmienić bo ona nie musi być z tego co rozumiem kwadratowa


## 18.11

Działa mi z jakiegoś chuja dopiero jak pobiore:

```sh
sudo apt-get install libbsd-dev
```
nie pamietam czy tak trzeba było przy so-long
