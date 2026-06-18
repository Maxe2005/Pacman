# Pacman

Un projet de Pacman en C avec la librairie SDL

## Avec docker

### 1. Autoriser l'accès local au serveur X (à refaire à chaque session si besoin)

```bash
xhost +local:root
```

### 2. Build l'image Docker

```bash
docker compose build
```

### 3. Lancer l'application

```bash
docker compose up
```


## Linux

### Ligne de compilation Ubuntu

```bash
gcc *.c -o prog -lSDL2 -lSDL2main -lSDL2_ttf -lm -lSDL2_mixer
```

### Pour installer toutes les dépendances

```bash
sudo apt update
sudo apt install $(grep -v '^#' requirements.txt)
```