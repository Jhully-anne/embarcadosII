# Metrônomo digital

## Docker
### Criar Container
``` 
docker run --name efm32 -it -v  C:\WorkSpace\Jhully\Hans:/home/trab ubuntu bash
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
