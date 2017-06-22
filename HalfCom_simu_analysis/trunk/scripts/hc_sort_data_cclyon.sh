#!/usr/bin/env bash
# hc_sort_data_cclyon.sh

debug=1

echo "Starting..." >&2

SW_PATH="/sps/nemo/scratch/golivier/software/Falaise/Analysis/sn_hc_simu_analysis/build/BuildProducts/bin"
SW_NAME="hc_sort_data"

function usage(){
echo "--------------"
echo "Goal : Sort half commissioning simulation data at CC Lyon."
echo "There is some rules for sorting linked with the real half commissioning"
echo "--------------"
echo "How to use it"
echo " "
echo "$ ./hc_sort_data_cclyon.sh [OPTIONS] [ARGUMENTS]"
echo ""
echo "Allowed options: "
echo "-h  [ --help ]     produce help message"
echo "-n  [ --number ]   set the number of events"
echo "-r  [--run-number] set the run number to analyze"
echo "-C  [--calo-mapping] set the calo mapping rules for sorting"
echo "-T  [--tracker-mapping] set the tracker mapping rules for sorting"
echo " "
echo "./hc_sort_data_cclyon.sh -r 0 -n number_of_events -C CALO_FILE -T TRACKER_FILE"
echo "Default value : number_of_events = 10"
echo " "
echo "--------------"
echo "Example : "
echo "./hc_sort_data.sh -n 100000 -r 0 -C CALO_FILE -T TRACKER_FILE"
echo " "
}

#### ->MAIN<- #####

START_DATE=`date "+%Y-%m-%d"`
nb_event=10
run_number=UNDEFINED
HC_CALO_MAPPING_CONFIG_FILE=UNDEFINED
HC_TRACKER_MAPPING_CONFIG_FILE=UNDEFINED

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
    if [ "x$arg" = "x-r" ]; then
	run_number=$arg_value
    fi
    if [ "x$arg" = "x-C" ]; then
	HC_CALO_MAPPING_CONFIG_FILE=$arg_value
    fi
    if [ "x$arg" = "x-T" ]; then
	HC_TRACKER_MAPPING_CONFIG_FILE=$arg_value
    fi
    shift 2
done

echo "RUN_NUMBER=" $run_number
echo "HC_CALO_MAPPING_CONFIG_FILE=" ${HC_CALO_MAPPING_CONFIG_FILE}
echo "HC_TRACKER_MAPPING_CONFIG_FILE=" ${HC_TRACKER_TRACKER_CONFIG_FILE}

INPUT_RUN_DIR="/sps/nemo/scratch/simu/golivier/damned_simu_${run_number}"
INPUT_SIMU_DIR="${INPUT_RUN_DIR}/output_files.d/"
INPUT_FILES=`ls -d ${INPUT_SIMU_DIR}/*.brio`

SORTED_OUTPUT_PATH="/sps/nemo/scratch/golivier/half_commissioning_simu/damned_simu_${run_number}/sorted_data"
MATCH_RULES_OUTPUT_PATH=${SORTED_OUTPUT_PATH}/match_rules
MATCH_RULES_WITH_GG_OUTPUT_PATH=${SORTED_OUTPUT_PATH}/match_rules_with_gg
LOG_DIR=${SORTED_OUTPUT_PATH}/log_files.d
CONF_DIR=${SORTED_OUTPUT_PATH}/conf.d

file_counter=0

for file in ${INPUT_FILES}
do
    INPUT_FILENAME=`basename $file .brio` # .brio after $file remove extension of the input file
    OUTPUT_FILENAME="output_sorted.brio"
    OUTPUT_WITH_GG_FILENAME="output_sorted_with_geiger.brio"

    LOG_FILE=${LOG_DIR}/${INPUT_FILENAME}_sorted.log

    echo "Mapping calo :" ${HC_CALO_MAPPING_CONFIG_FILE}
    echo "Mapping tracker :" ${HC_TRACKER_MAPPING_CONFIG_FILE}

    echo "Starting process..."
    echo "Processing..."

    ${SW_PATH}/${SW_NAME} -i ${file} -o ${SORTED_OUTPUT_PATH}/ -n $nb_event -C ${HC_CALO_MAPPING_CONFIG_FILE} -T ${HC_TRACKER_MAPPING_CONFIG_FILE} > ${LOG_FILE} 2>&1
    if [ $? -eq 1 ];
    then
	echo "ERROR : command ${SW_PATH}/${SW_NAME} -i ${file} -o ${SORTED_OUTPUT_PATH}/ -n $nb_event -C ${HC_CALO_MAPPING_CONFIG_FILE} -T ${HC_TRACKER_MAPPING_CONFIG_FILE} > ${LOG_FILE} 2>&1 FAILED !" >> ${LOG_FILE}
	echo "FILE_SORTING:FAILED" >> ${LOG_FILE}
	exit 0
    fi

    mv ${SORTED_OUTPUT_PATH}/${OUTPUT_FILENAME} ${MATCH_RULES_OUTPUT_PATH}/${INPUT_FILENAME}_sorted.brio
    if [ $? -eq 1 ];
    then
	echo "ERROR : mv ${SORTED_OUTPUT_PATH}/${OUTPUT_FILENAME} into ${SORTED_OUTPUT_PATH}/${INPUT_FILENAME}_sorted.brio FAILED !"
	exit 0
    fi

    mv ${SORTED_OUTPUT_PATH}/${OUTPUT_WITH_GG_FILENAME} ${MATCH_RULES_WITH_GG_OUTPUT_PATH}/${INPUT_FILENAME}_sorted_with_gg.brio
    if [ $? -eq 1 ];
    then
	echo "ERROR : mv ${SORTED_OUTPUT_PATH}/${OUTPUT_WITH_GG_FILENAME} into ${SORTED_OUTPUT_PATH}/${INPUT_FILENAME}_sorted_with_gg.brio FAILED !"
	exit 0
    fi

    echo "FILE_SORTING:SUCCESS" >> ${LOG_FILE}
    let file_counter++

    echo "Ending process..."
done
