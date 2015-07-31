'use strict';

module.exports = function(grunt) {

  grunt.initConfig({
    msbuild: {
		tests:{
			src: ['zTestCpp.sln'],
            options: {
                projectConfiguration: 'Debug',
                targets: ['zTestCpp'],
                version: 12.0,
                maxCpuCount: 4,
                buildParameters: {
                    WarningLevel: 4
                },
                verbosity: 'minimal'
            }
		}
    },
    watch: {
		tests: {
			files: ['zTestCpp/**/*.cpp','zTestCpp/**/*.h'],
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