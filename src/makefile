COMP = icc
OBJ = main.o conv_pos.o func.o glob_opt.o init_struct.o i_o.o lammps.o loc_opt.o \
	  pair.o pso_chi.o pso.o pso_opt.o randomlib.o vasp.o potfit.o adaptive.o diff_evol.o

search: $(OBJ)
	$(COMP) -o search $(OBJ)

main.o:	main.cpp paras.h init_struct.h glob_opt.h
	$(COMP) -c main.cpp

conv_pos.o: conv_pos.cpp conv_pos.h
	$(COMP) -c conv_pos.cpp

func.o: func.cpp func.h
	$(COMP) -c func.cpp

glob_opt.o: glob_opt.cpp glob_opt.h
	$(COMP) -c glob_opt.cpp

init_struct.o: init_struct.cpp init_struct.h func.h
	$(COMP) -c init_struct.cpp

i_o.o: i_o.cpp i_o.h
	$(COMP) -c i_o.cpp

lammps.o: lammps.cpp lammps.h
	$(COMP) -c lammps.cpp

loc_opt.o: loc_opt.cpp loc_opt.h
	$(COMP) -c loc_opt.cpp

pair.o: pair.cpp pair.h
	$(COMP) -c pair.cpp

pso_chi.o: pso_chi.cpp pso_chi.h
	$(COMP) -c pso_chi.cpp

pso.o: pso.cpp pso.h
	$(COMP) -c pso.cpp

pso_opt.o: pso_opt.cpp pso_opt.h
	$(COMP) -c pso_opt.cpp

randomlib.o: randomlib.cpp randomlib.h
	$(COMP) -c randomlib.cpp

vasp.o: vasp.cpp vasp.h
	$(COMP) -c vasp.cpp

potfit.o: potfit.cpp potfit.h
	$(COMP) -c potfit.cpp

adaptive.o: adaptive.cpp adaptive.h
	$(COMP) -c adaptive.cpp

diff_evol.o: diff_evol.cpp diff_evol.h
	$(COMP) -c diff_evol.cpp


clean:
	rm -rf $(OBJ) search
