# Cube3d

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
