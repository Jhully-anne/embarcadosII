# Metrônomo digital

## Projeto
* Entradas
  * Ler valor do potenciômetro (20, 200)
  * Botão muda o compasso
* Saídas

## Comandos
### Compilar
```
make all
```
### Gravar na placa
```
sudo make flash
```

## Docker
### Criar Container
``` 
docker-compose up
docker-compose exec embarcados2 bash -c 'cd /home/embarcados; exec bash'
```
### Iniciar Container existente
```
 docker container exec -it efm32 /bin/bash
```

### Compilador
```
apt-get update
apt-get install gcc-arm-none-eabi binutils-arm-none-eabi gdb-arm-none-eabi
```

## Executar
