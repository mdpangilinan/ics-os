#!/bin/bash

# BUILDS ICS-OS
	cd ../..
	make clean
	make vmdex
	make floppy

# BOOTS ICS-OS
	make boot-floppy
