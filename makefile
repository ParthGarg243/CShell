all: main date dir

main: q2_main.c
	gcc q2_dir.c -o main
date: q2_date.c
	gcc q2_date.c -o date
dir: q2_dir.c
	gcc q2_dir.c -o dir
