'use strict';

module.exports = function(grunt) {

  grunt.initConfig({
    msbuild: {
		tests:{
			src: ['zTestCpp.sln'],
            options: {
                projectConfiguration: 'Debug',
                targets: ['Tests'],
                version: 12.0,
                maxCpuCount: 4,
                buildParameters: {
                    WarningLevel: 4
                },
                verbosity: 'quiet'
            }
		}
    },
    watch: {
		tests: {
			files: ['zTestCpp/**/*.cpp','zTestCpp/**/*.h','Tests/**/*.cpp','Tests/**/*.h'],
			tasks: ['msbuild:tests'],
			options: {
				  spawn: false,
			},
		},
    }
  });

  grunt.loadNpmTasks('grunt-msbuild');
  grunt.loadNpmTasks('grunt-contrib-watch');
 
  grunt.registerTask('default', ['watch']);

};