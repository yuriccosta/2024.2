# Loop infinito
while true; do
  # Aguarda a entrada do usuário
  read -p "Pressione Enter para executar o comando: " input
  
  gcc atividade2.c -o exec -lglut -lGL -lGLU -lm
  ./exec
done


