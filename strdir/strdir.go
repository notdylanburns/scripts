package main

import (
	"fmt"
	"io/ioutil"
	"os"
	fp "path/filepath"
	s "strings"
)

const SPACING uint8 = 2

const (
	NONE 		= ' '
	PIPE 		= '|'
	CROSS		= '+'
	BACKTICK 	= '`'
	DASH		= '-'
	SPACE 		= ' '
)


func strdir(path string, sections []uint8) {
	var depth int = len(sections) - 1

	content, e := ioutil.ReadDir(path)
	if (e != nil) {
		panic(e)
	}

	fileCount := len(content)

	for fileIndex, file := range content {
		// empty condition - prev was either empty or '`'

		// if this is the last file in the dir
	
		for i, prev := range sections {
			// if this is a the final section
			if (i == depth) {
				sections[i] = CROSS
			} else {
				switch (prev) {
				case NONE:
				case BACKTICK:
					sections[i] = NONE
					break
				case PIPE:
				case CROSS:
					sections[i] = PIPE
				}
			}

			if (fileIndex == fileCount - 1) {
				sections[depth]	= BACKTICK	
			}
		}

			// print sections
		for _, sect := range sections {
			fmt.Printf("%*c%c", SPACING, ' ', sect)
		}		

		fmt.Printf("%c", DASH)
		if (file.Mode() & os.ModeSymlink == os.ModeSymlink) {
			f, _ := fp.EvalSymlinks(s.Join([]string{path, file.Name()}, "/"))
			fmt.Printf("%s -> %s\n", file.Name(), f)
		} else {
			fmt.Printf("%s\n", file.Name())
			if (file.IsDir()) {
				strdir(s.Join([]string{path, file.Name()}, "/"), append(sections, PIPE))
			}
		} 

	}

}

func main() {
	var path string
	if (len(os.Args) > 1) {
		path = os.Args[1]
	} else {
		dirs := s.Split(os.Args[0], "/")
		var shortpath string = s.Join(dirs[:len(dirs) - 1], "/")
		os.Chdir(shortpath)
		path, _ = os.Getwd()
	}
	
	fmt.Printf("%s/:\n", path)

	strdir(path, []uint8{PIPE})

	// array with length of number of parent directories
}