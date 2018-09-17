package main

import (
	"bufio"
	"errors"
	"fmt"
	"os"
	"os/user"
)

// Binary is a struct that represents a program
type Binary struct {
	Name            string
	DesktopFilePath string
	IconFilePath    string
	Path            string
}

// Config is a struct that holds all file information
type Config struct {
	Bins []Binary
	Path string
}

const (
	localPath     = ".local/share/binmgr"
	confFileName  = "binmgr.conf"
	binFolderName = "bins"
)

func getConfigPath() (string, error) {
	usr, err := user.Current()
	if err != nil {
		return "", err
	}
	return usr.HomeDir + "/" + localPath + "/" + confFileName, nil
}

func getBinDir() (string, error) {
	usr, err := user.Current()
	if err != nil {
		return "", err
	}
	return usr.HomeDir + "/" + localPath + "/" + binFolderName, nil
}

func configToReal(config string) (string, error) {
	if config[0] != ':' {
		return "", fmt.Errorf("Invalid config path '%s'", config)
	}
	translatable := []rune(config)
	for i := range translatable {
		if translatable[i] == ':' {
			translatable[i] = '/'
		}
	}
	return string(translatable), nil
}

func realToConfig(real string) (string, error) {
	if real[0] != '/' {
		return "", fmt.Errorf("Invalid path '%s'", real)
	}
	translatable := []rune(real)
	for i := range translatable {
		if translatable[i] == '/' {
			translatable[i] = ':'
		}
	}
	return string(translatable), nil
}

// RepairBins makes sure all linked bins exist
func (c *Config) RepairBins() error {

	return nil
}

// ParseConfig parses the config's path, populating Bins
func (c *Config) ParseConfig() error {
	var err error
	c.Path, err = getConfigPath()
	if err != nil {
		return err
	}
	configFile, err := os.Open(c.Path)
	if err != nil {
		return err
	}
	defer configFile.Close()
	configScanner := bufio.NewScanner(configFile)

	curElem := 0
	curBinary := Binary{}
	for configScanner.Scan() {
		switch curElem {
		case 0:
			curBinary.Name = configScanner.Text()
			break
		case 1:
			curBinary.DesktopFilePath = configScanner.Text()
			break
		case 2:
			curBinary.IconFilePath = configScanner.Text()
			break
		case 3:
			curBinary.Path = configScanner.Text()
			curBinary.DesktopFilePath, err = configToReal(curBinary.DesktopFilePath)
			if err != nil {
				return err
			}
			curBinary.IconFilePath, err = configToReal(curBinary.IconFilePath)
			if err != nil {
				return err
			}
			curBinary.Path, err = configToReal(curBinary.Path)
			if err != nil {
				return err
			}
			c.Bins = append(c.Bins, curBinary)
			curElem = -1
			break
		default:
			return errors.New("Internal state machine error")
		}
		curElem++
	}
	if err := configScanner.Err(); err != nil {
		return err
	}
	if curElem != 0 {
		return fmt.Errorf("invalid config file, ended on %d", curElem)
	}
	return nil
}
