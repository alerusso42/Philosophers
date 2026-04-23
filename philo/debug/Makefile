DEBUG_FILE = ../g.gdb
SUPPRESSION_FILE = ../s.supp
S1 = ../die_track.sh
S2 = ../count_meal.sh

debug: $(DEBUG_FILE) $(SUPPRESSION_FILE) $(S1) $(S2)

$(DEBUG_FILE): 
	@echo "define a\
		\n\tset \$$i = 0\
		\n\twhile (\$$i < a->size)\
		\n\t\tp a->data[a->first + \$$i]\
		\n\t\tset \$$i = \$$i + 1\
		\n\tend\
		\n\tp a->size\
		\nend\
		\n\ndefine b\
		\n\tset \$$i = 0\
		\n\twhile (\$$i < b->size)\
		\n\t\tp b->data[b->first + \$$i]\
		\n\t\tset \$$i = \$$i + 1\
		\n\tend\
		\n\tp b->size\nend" > $(DEBUG_FILE);

$(SUPPRESSION_FILE): 
	@echo "# IGNORE OTHER EXECUTABLES' LEAKS\
		\n{\
		\n\tMALLOC FAILURE OF /usr/bin/*\
		\n\tMemcheck:Leak\
		\n\tfun:malloc\
		\n\t...\
		\n\tobj:/usr/bin/*\
		\n}\
		\n{\
		\n\tCALLOC FAILURE of /usr/bin/*\
		\n\tMemcheck:Leak\
		\n\tfun:calloc\
		\n\t...\
		\n\tobj:/usr/bin/*\
		\n}\
		\n{\
		\n\tREALLOC FAILURE of /usr/bin/*\
		\n\tMemcheck:Leak\
		\n\tfun:realloc\
		\n\t...\
		\n\tobj:/usr/bin/*\
		\n}" > $(SUPPRESSION_FILE);

$(S1):
	@echo "#!/bin/bash"                                      >  $(S1)
	@echo ""                                                >> $(S1)
	@echo "NPHILO=\"5\""                                    >> $(S1)
	@echo "TIME_DIE=\"405\""                                >> $(S1)
	@echo "TIME_EAT=\"200\""                                >> $(S1)
	@echo "TIME_SLEEP=\"200\""                              >> $(S1)
	@echo "N_EAT=\"\""                                      >> $(S1)
	@echo ""                                                >> $(S1)
	@echo "clear"                                           >> $(S1)
	@echo "philo_output=\"./philo \$$NPHILO \$$TIME_DIE \$$TIME_EAT \$$TIME_SLEEP \$$N_EAT\"" >> $(S1)
	@echo "\$$philo_output | awk '"                         >> $(S1)
	@echo "/died/ { died_id = \$$2 }"                       >> $(S1)
	@echo "{ lines[NR] = \$$0; ids[NR] = \$$2 }"            >> $(S1)
	@echo "END {"                                           >> $(S1)
	@echo "    for (i = 1; i <= NR; i++) {"                 >> $(S1)
	@echo "        if (ids[i] == died_id)"                 >> $(S1)
	@echo "            print \"\\033[1;31m\" lines[i] \"\\033[0m\";" >> $(S1)
	@echo "        else"                                   >> $(S1)
	@echo "            print lines[i];"                    >> $(S1)
	@echo "    }"                                           >> $(S1)
	@echo "}'"                                              >> $(S1)
	@chmod +x $(S1)

$(S2):
	@echo "#!/bin/bash"                                      >  $(S2)
	@echo ""                                                >> $(S2)
	@echo "NPHILO=\"5\""                                    >> $(S2)
	@echo "TIME_DIE=\"405\""                                >> $(S2)
	@echo "TIME_EAT=\"200\""                                >> $(S2)
	@echo "TIME_SLEEP=\"200\""                              >> $(S2)
	@echo "N_EAT=\"\""                                      >> $(S2)
	@echo ""                                                >> $(S2)
	@echo "clear"                                           >> $(S2)
	@echo "philo_output=\"./philo \$$NPHILO \$$TIME_DIE \$$TIME_EAT \$$TIME_SLEEP \$$N_EAT\"" >> $(S2)
	@echo "\$$philo_output | awk '"                         >> $(S2)
	@echo "/died/ { died_id = \$$2 }"                       >> $(S2)
	@echo "{ lines[NR] = \$$0; ids[NR] = \$$2 }"            >> $(S2)
	@echo "END {"                                           >> $(S2)
	@echo "    for (i = 1; i <= NR; i++) {"                 >> $(S2)
	@echo "        if (ids[i] == died_id)"                 >> $(S2)
	@echo "            print \"\\033[1;31m\" lines[i] \"\\033[0m\";" >> $(S2)
	@echo "        else"                                   >> $(S2)
	@echo "            print lines[i];"                    >> $(S2)
	@echo "    }"                                           >> $(S2)
	@echo "}' | grep \" 0 is eating\" | wc -l"		  		>> $(S2)
	@chmod +x $(S2)

.SILENT: 