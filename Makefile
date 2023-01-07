SERVER = server

NAME = client

HEADER = minitalk.h ft_printf/ft_printf.h

SCLIENT = client.c

SSERVER = server.c

BSERVER = server_bonus

BNAME = client_bonus

BHEADER = minitalk_bonus.h ft_printf/ft_printf.h

BSCLIENT = client_bonus.c

BSSERVER = server_bonus.c

SRC =  ft_printf/ft_printf.c ft_printf/ft_printchar.c ft_printf/ft_puthexa.c ft_printf/ft_puthexam.c ft_printf/ft_putnbr.c ft_printf/ft_putnbrun.c\
		ft_printf/ft_putpoint.c ft_printf/ft_putstr.c 

CC = cc

CFLAGS = -Wall -Werror -Wextra

all: $(NAME) $(SERVER)
	
$(SERVER): $(SSERVER) $(SRC) $(HEADER)
	@$(CC) $(CFLAGS) $(SSERVER) $(SRC) -o server
	
$(NAME): $(SCLIENT) $(SRC) $(HEADER)
	@$(CC) $(CFLAGS) $(SCLIENT) $(SRC) -o client

bonus: $(BNAME) $(BSERVER)

$(BSERVER): $(BSSERVER) $(SRC) $(BHEADER)
	@$(CC) $(CFLAGS) $(BSSERVER) $(SRC) -o server_bonus

$(BNAME): $(BSCLIENT) $(SRC) $(BHEADER)
	@$(CC) $(CFLAGS) $(BSCLIENT) $(SRC) -o client_bonus

clean:
	rm -f $(NAME) $(SERVER) $(BNAME) $(BSERVER)

fclean: clean

re: fclean 
