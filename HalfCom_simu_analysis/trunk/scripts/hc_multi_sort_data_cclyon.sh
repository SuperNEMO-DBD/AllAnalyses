#!/usr/bin/env bash
# hc_multi_sort_data_cclyon.sh

debug=1

echo "Starting..." >&2

function usage(){
echo "--------------"
echo "Goal : Mult Sort half commissioning simulation data with qsubs at CC Lyon."
echo "There is some rules for sorting linked with the real half commissioning"
echo "Don't forget to adapt the script for your runs, RUN_MIN RUN_MAX and mapping calo & tracker"
echo "--------------"
echo "How to use it"
echo " "
echo "$ ./hc_multi_sort_data_cclyon.sh [OPTIONS] [ARGUMENTS]"
echo ""
echo "Allowed options: "
echo "-h  [ --help ]     produce help message"
echo "-n  [ --number ]   set the number of events"
echo " "
echo "./hc_multi_sort_data_cclyon.sh -n number_of_events"
echo "Default value : number_of_events = 10"
echo " "
echo "--------------"
echo "Example : "
echo "./hc_multi_sort_data_cclyon.sh -n 100000"
echo " "
}

#### ->MAIN<- #####

START_DATE=`date "+%Y-%m-%d"`
nb_event=10

while [ -n "$1" ];
do
    arg="$1"
    arg_value="$2"
    if [ "x$arg" = "x-h" -o "x$arg" = "x--help" ]; then
        usage
        exit 0
    fi
    if [ "x$arg" = "x-n" ]; then
        nb_event=$arg_value
    fi
    shift 2
done

SCRIPT_DIR=/sps/nemo/scratch/golivier/software/Falaise/Analysis/sn_hc_simu_analysis/trunk/scripts
SINGLE_SORT_SCRIPT=hc_sort_data_cclyon.sh

# Change Run min / max 
RUN_MIN=0
RUN_MAX=21

for (( i=${RUN_MIN}; i <= ${RUN_MAX}; ++i ))
do
    echo "RUN_NUMBER=" ${i}
    
    SORTED_OUTPUT_PATH="/sps/nemo/scratch/golivier/half_commissioning_simu/damned_simu_${i}/sorted_data"
    MATCH_RULES_OUTPUT_PATH=${SORTED_OUTPUT_PATH}/match_rules
    MATCH_RULES_WITH_GG_OUTPUT_PATH=${SORTED_OUTPUT_PATH}/match_rules_with_gg
    LOG_DIR=${SORTED_OUTPUT_PATH}/log_files.d
    CONF_DIR=${SORTED_OUTPUT_PATH}/conf.d
    LOG_FILE=${LOG_DIR}/multi_sort.log
    mkdir -p ${SORTED_OUTPUT_PATH} ${MATCH_RULES_OUTPUT_PATH} ${MATCH_RULES_WITH_GG_OUTPUT_PATH} ${LOG_DIR} ${CONF_DIR}
    if [ $? -eq 1 ];
    then
	echo "ERROR : mkdir ${SORTED_OUTPUT_PATH} or ${MATCH_RULES_OUTPUT_PATH} or ${MATCH_RULES_WITH_GG_OUTPUT_PATH} or ${LOG_DIR} FAILED !" >> ${LOG_FILE}
	exit 0
    fi    

    echo "****** MULTI SORT GENERAL LOG FILE RUN_${i}" > ${LOG_FILE} 2>&1
    
    # Change sorting mapping 
    # Here : 1 column calo + 1 row tracker
    HC_CALO_MAPPING_CONFIG_FILE=/sps/nemo/scratch/golivier/hc_simu_sorted_mapping/run_1_col/mapping_calo.conf
    HC_TRACKER_MAPPING_CONFIG_FILE=/sps/nemo/scratch/golivier/hc_simu_sorted_mapping/run_1_col/mapping_tracker.conf
    echo "HC_CALO_MAPPING_CONFIG_FILE    =" ${HC_CALO_MAPPING_CONFIG_FILE} >> ${LOG_FILE}
    echo "HC_TRACKER_MAPPING_CONFIG_FILE =" ${HC_TRACKER_MAPPING_CONFIG_FILE} >> ${LOG_FILE}

    cp ${HC_CALO_MAPPING_CONFIG_FILE} ${CONF_DIR}
    if [ $? -eq 1 ];
    then    
	echo "ERROR : cannot copy ${HC_CALO_MAPPING_CONFIG_FILE} into ${CONF_DIR} FAILED !" >> ${LOG_FILE}
	exit 0
    fi

    cp ${HC_TRACKER_MAPPING_CONFIG_FILE} ${CONF_DIR}
    if [ $? -eq 1 ];
    then    
	echo "ERROR : cannot copy ${HC_TRACKER_MAPPING_CONFIG_FILE} into ${CONF_DIR} FAILED !" >> ${LOG_FILE}
	exit 0
    fi
    
    qsub -V -P P_nemo -l h_cpu=12:00:00,s_cpu=11:30:00,fsize=8000M,sps=1 -e ${LOG_DIR} -o ${LOG_DIR} ${SCRIPT_DIR}/${SINGLE_SORT_SCRIPT} -r ${i} -n ${nb_event} -C ${HC_CALO_MAPPING_CONFIG_FILE} -T ${HC_TRACKER_MAPPING_CONFIG_FILE} >> ${LOG_FILE}
    
done