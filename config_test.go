package main

import (
	"bufio"
	"os"
	"testing"

	"github.com/stretchr/testify/require"
)

const (
	mockConfigName = ".mockc.config"
)

// createMockConfigFile creates a mock config file
func createMockConfigFile(r *require.Assertions) {
	fo, err := os.Create(mockConfigName)
	r.Nil(err)
	defer func() {
		err := fo.Close()
		r.Nil(err)
	}()
	w := bufio.NewWriter(fo)
	_, err = w.WriteString("Testing")
	r.Nil(err)
}

// deleteConfigFile deletes the temporary config file
func deleteConfigFile(r *require.Assertions) {
	err := os.Remove(mockConfigName)
	r.Nil(err)
}

func TestParseConfig(t *testing.T) {
	require := require.New(t)
	createMockConfigFile(require)
	defer deleteConfigFile(require)

	mockConfig := &Config{}
	mockConfig.Path = mockConfigName
	err := mockConfig.ParseConfig()
	require.Nil(err)
}
