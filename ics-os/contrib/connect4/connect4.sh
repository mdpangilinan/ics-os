#!/bin/bash

# RUNS MAKEFILE
	make
	make install
	cd ../..

# BUILDS ICS-OS	
	make clean
	make vmdex
	make floppy

# BOOTS ICS-OS
	make boot-floppy
