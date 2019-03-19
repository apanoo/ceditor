package main

import (
	"fmt"
	"os"

	"github.com/spf13/cobra"
)

// default command
var rootCmd = &cobra.Command{
	Use:   "bustm",
	Short: "bustm is a cross platform build system with lua script",
	Long: `
               __               __          
              / /_  __  _______/ /_____ ___ 
             / __ \/ / / / ___/ __/ __ .__ \
            / /_/ / /_/ (__  ) /_/ / / / / /
           /_.___/\__,_/____/\__/_/ /_/ /_/ 
A Fast and Flexible cross platform build system, you can write
a lua script pipe to build everything by external tools.
Complete sources code is available at https://github.com/apanoo/ceditor
`,
	Run: func(cmd *cobra.Command, args []string) {
		// Do Stuff Here
	},
}

// Execute root cmd run
func Execute() {
	if err := rootCmd.Execute(); err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
}

func init() {
	rootCmd.AddCommand(versionCmd)
	rootCmd.AddCommand(luaCmd)
}

////////////////////// sub command ////////////////////////
var versionCmd = &cobra.Command{
	Use:   "version",
	Short: "Print the version number of bustm",
	Long:  `All software has versions. This is bustm's`,
	Run: func(cmd *cobra.Command, args []string) {
		fmt.Println("bustm v0.1.1 -- HEAD")
	},
}

var luaCmd = &cobra.Command{
	Use:   "lua",
	Short: "Test lua script execute by golang bustm",
	Long:  `Execute a lua script from build system with open API`,
	Run: func(cmd *cobra.Command, args []string) {
		testLua(args)
	},
}
