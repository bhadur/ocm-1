pipeline {
    agent {
        node {
          label 'EdgeCSP_01'
        }
      
    }
     environment {
        GITLAB_LOGIN = credentials('Intel-Gitlab')
        CURRENT_DATE = sh(script: 'date +"%Y-%m-%d_%H-%M-%S"', returnStdout: true).trim()
        PROJECT_NAME = "ocm" //Needs to be similar to Gitlab Project name
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
                   #cp kw_report.zip artifacts
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
         
            
     }

  }
