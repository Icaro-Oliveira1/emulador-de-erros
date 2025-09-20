# emulador-de-erros

# Primeiro, compilamos tudo de uma vez com o Makefile

make

# Depois, executamos o emulador para um erro específico

bash emulador.sh stack_overflow
bash emulador.sh deadlock
bash emulador.sh memory_leak

# Para executar localmente com docker

docker build -t emulador-local .
docker run --rm emulador-local stack_overflow
