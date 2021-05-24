pipeline {
    agent {
        node {
          label 'EdgeCSP_01'
        }
      
    }
     environment {
        GITLAB_LOGIN = credentials('Intel-Gitlab')
        CURRENT_DATE = sh(script: 'date +"%Y-%m-%d_%H-%M-%S"', returnStdout: true).trim()
        PROJECT_NAME = "ocm"
        GITLAB_BRANCH = "master"
    }
         
     stages {
            stage('Checkout SCM') {
               steps{
                   sh '''#!/bin/bash
                      #uname -a
                      #mkdir artifacts
                      #git clone https://github.com/bhadur/ocm.git
                      
                   '''
                }
    	    }
             
                   
            stage('Scan: Klocwork') {
               steps{
                
                   sh '''#!/bin/bash
                   mkdir ../artifacts-ocm
                   KWPROJ_NAME=OCM
                   pwd
                   sed -i "s|^make|/home/ubuntu/kw2020/bin/kwinject make|g" build_ocm.sh
                   source /home/ubuntu/ocm_tf_setup/ocm_venv/bin/activate
                   pip install /home/ubuntu/ocm_tf_setup/tensorflow/tensorflow-2.4.1-cp36-cp36m-linux_x86_64.whl
                   bash build_ocm.sh /home/ubuntu/ocm_tf_setup
                   cd build
                   /home/ubuntu/kw2020/bin/kwbuildproject --force --verbose --license-host klocwork05p.elic.intel.com --license-host 7500 --url https://klocwork-jf24.devtools.intel.com:8190/${KWPROJ_NAME} -o ${KWPROJ_NAME}_Tables kwinject.out
                   /home/ubuntu/kw2020/bin/kwadmin --url https://klocwork-jf24.devtools.intel.com:8190 load ${KWPROJ_NAME} ${KWPROJ_NAME}_Tables --name $(date +"%Y-%m-%d_%H-%M-%S")
                   cd $WORKSPACE
                   python3 /home/ubuntu/OWR_klocwork_report.py --server https://klocwork-jf24.devtools.intel.com --port 8190 --project ${KWPROJ_NAME} --build build_kw --output kw_report_ocm.html
                   zip -r kw_report.zip kw_report_ocm.html
                   cp kw_report.zip ../artifacts-ocm
                   rm -rf build
                   '''    
                 }
            }
        
        stage('Upload: Kw Reports'){
            steps{
                    rtUpload (
                        serverId: 'software-recipes-artifactory',
                        spec: '''{
                              "files": [
                                {
                                  "pattern": "kw_report.zip",
                                  "target": "software-recipes-or-local/scan-reports/${PROJECT_NAME}/${CURRENT_DATE}/kw_report.zip"
                                }
                             ]
                        }'''
                    )
                
                }
        }
         
         stage('Scan: Checkmarx') {
            steps{
                echo "Executing Checkmarx Jenkins Plugin to request a Scan"
                step([$class: 'CxScanBuilder', comment: '', credentialsId: 'Checkmarx', excludeFolders: '', exclusionsSetting: 'global', failBuildOnNewResults: false, failBuildOnNewSeverity: 'HIGH', filterPattern: '''!**/_cvs/**/*, !**/.svn/**/*,   !**/.hg/**/*,   !**/.git/**/*,  !**/.bzr/**/*, !**/bin/**/*,
!**/obj/**/*,  !**/backup/**/*, !**/.idea/**/*, !**/*.DS_Store, !**/*.ipr,     !**/*.iws,
!**/*.bak,     !**/*.tmp,       !**/*.aac,      !**/*.aif,      !**/*.iff,     !**/*.m3u, !**/*.mid, !**/*.mp3,
!**/*.mpa,     !**/*.ra,        !**/*.wav,      !**/*.wma,      !**/*.3g2,     !**/*.3gp, !**/*.asf, !**/*.asx,
!**/*.avi,     !**/*.flv,       !**/*.mov,      !**/*.mp4,      !**/*.mpg,     !**/*.rm,  !**/*.swf, !**/*.vob,
!**/*.wmv,     !**/*.bmp,       !**/*.gif,      !**/*.jpg,      !**/*.png,     !**/*.psd, !**/*.tif, !**/*.swf,
!**/*.jar,     !**/*.zip,       !**/*.rar,      !**/*.exe,      !**/*.dll,     !**/*.pdb, !**/*.7z,  !**/*.gz,
!**/*.tar.gz,  !**/*.tar,       !**/*.gz,       !**/*.ahtm,     !**/*.ahtml,   !**/*.fhtml, !**/*.hdm,
!**/*.hdml,    !**/*.hsql,      !**/*.ht,       !**/*.hta,      !**/*.htc,     !**/*.htd, !**/*.war, !**/*.ear,
!**/*.htmls,   !**/*.ihtml,     !**/*.mht,      !**/*.mhtm,     !**/*.mhtml,   !**/*.ssi, !**/*.stm,
!**/*.stml,    !**/*.ttml,      !**/*.txn,      !**/*.xhtm,     !**/*.xhtml,   !**/*.class, !**/*.iml, !Checkmarx/Reports/*.*''', fullScanCycle: 10, generatePdfReport: true, groupId: '22f6feaa-42cb-4380-bd7e-a01e731963d6', password: '{AQAAABAAAAAQMWVJN9G3AAHlL4dK5kiik62UdPPdFAppOZUSKCpIR3U=}', preset: '36', projectName: 'OCM', sastEnabled: true, serverUrl: 'https://sast.intel.com/', sourceEncoding: '1', useOwnServerCredentials: true, username: '', vulnerabilityThresholdResult: 'FAILURE', waitForResultsEnabled: true])

            sh '''
                zip -r checkmarx.zip Checkmarx/
                cp checkmarx.zip artifacts
            '''
            }

        }

        stage('Upload: Checkmarx Reports'){
        steps{
                rtUpload (
                    serverId: 'software-recipes-artifactory',
                    spec: '''{
                          "files": [
                            {
                              "pattern": "checkmarx.zip",
                              "target": "software-recipes-or-local/scan-reports/${PROJECT_NAME}/${CURRENT_DATE}/checkmarx.zip"
                            }
                         ]
                    }'''
                )
            
            }
        }
         
            
     }

  }
