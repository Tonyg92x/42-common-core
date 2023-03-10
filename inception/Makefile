# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguay <aguay@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/21 08:36:50 by aguay             #+#    #+#              #
#    Updated: 2022/10/27 10:09:00 by aguay            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: up

up: build
	@mkdir -p /home/aguay/data/wordpress
	@mkdir -p /home/aguay/data/mariadb
	@docker-compose -f srcs/docker-compose.yml up -d
	@docker ps

build:	srcs/docker-compose.yml
	@docker-compose -f srcs/docker-compose.yml build

down:
	@docker-compose -f srcs/docker-compose.yml down
	@docker ps

clean:
	@docker-compose -f srcs/docker-compose.yml down --rmi all

vclean:
	@docker volume rm srcs_volume-mariadb
	@docker volume rm srcs_volume-wordpress

fclean:	clean vclean

re: fclean all

.PHONY: all up down build clean vclean fclean re
