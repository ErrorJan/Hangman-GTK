#!/bin/python3
import sys;
import os;
from pathlib import Path
from shutil import copytree
from shutil import copy
from shutil import rmtree

# Variables
OUTPUT_DIR = "Hangman_in_GTK"
RESOURCES_DIR = "resources"

binFullPath = sys.argv[ 1 ];

dirFullPathSplit = binFullPath.split( '/' );

#binName = dirFullPathSplit[ len( dirFullPathSplit ) - 1 ];

dirFullPathSplit.pop( len( dirFullPathSplit ) - 1 );

dirFullPath = '/'.join( dirFullPathSplit );
# Variables

# Check
if not os.path.exists( binFullPath ):
    exit()

# Check

# IO stuff
if ( os.path.exists( dirFullPath + "/" + OUTPUT_DIR ) ):
    rmtree( dirFullPath + "/" + OUTPUT_DIR );

Path( dirFullPath + "/" + OUTPUT_DIR ).mkdir( parents=True, exist_ok=True );

copytree( RESOURCES_DIR, dirFullPath + "/" + OUTPUT_DIR + "/" + RESOURCES_DIR );

copy( binFullPath, dirFullPath + "/" + OUTPUT_DIR );
# IO stuff