#!/usr/bin/env bash
# hc_sort_data.sh

debug=1

echo "Starting..." >&2

SW_PATH="/home/goliviero/software/Falaise/Analysis/sn_hc_simu_analysis/build/BuildProducts/bin"
SW_NAME="hc_sort_data"

function usage(){
echo "--------------"
echo "Goal : Sort half commissioning simulation data."
echo "There is some rules for sorting linked with the real half commissioning"
echo "--------------"
echo "How to use it"
echo " "
echo "$ ./hc_sort_data [OPTIONS] [ARGUMENTS]"
echo ""
echo "Allowed options: "
echo "-h  [ --help ]     produce help message"
echo "-n  [ --number ]   set the number of events"
echo "-r  [--run-number] set the run number to analyze"
echo " "
echo "./hc_sort_data.sh -n number_of_events"
echo "Default value : number_of_events = 10"
echo " "
echo "--------------"
echo "Example : "
echo "./hc_sort_data.sh -n 100000 -r 0"
echo " "
}

#### ->MAIN<- #####

START_DATE=`date "+%Y-%m-%d"`
nb_event=10
run_number=UNDEFINED

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
    shift 2
done

echo "RUN_NUMBER=" $run_number

INPUT_RUN_DIR="${DATA_NEMO_PERSO_DIR}/half_commissioning_simu/run_${run_number}"
INPUT_SIMU_DIR="${INPUT_RUN_DIR}/simu_data/"
INPUT_FILES=`ls -d ${INPUT_SIMU_DIR}/*.brio`

SORTED_OUTPUT_PATH="${DATA_NEMO_PERSO_DIR}/half_commissioning_simu/run_${run_number}/sorted_data"
MATCH_RULES_OUTPUT_PATH=${SORTED_OUTPUT_PATH}/match_rules
MATCH_RULES_WITH_GG_OUTPUT_PATH=${SORTED_OUTPUT_PATH}/match_rules_with_gg
LOG_DIR=${SORTED_OUTPUT_PATH}/log_files.d

mkdir -p ${SORTED_OUTPUT_PATH} ${MATCH_RULES_OUTPUT_PATH} ${MATCH_RULES_WITH_GG_OUTPUT_PATH} ${LOG_DIR}
if [ $? -eq 1 ];
then
    echo "ERROR : mkdir ${SORTED_OUTPUT_PATH} or ${MATCH_RULES_OUTPUT_PATH} or ${MATCH_RULES_WITH_GG_OUTPUT_PATH} or ${LOG_DIR} FAILED !"
    exit 0
fi

HC_CALO_MAPPING_CONFIG_FILE=${INPUT_RUN_DIR}/hc_mapping/mapping_calo.conf
HC_TRACKER_MAPPING_CONFIG_FILE=${INPUT_RUN_DIR}/hc_mapping/mapping_tracker.conf

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
