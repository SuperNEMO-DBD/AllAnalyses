#!/usr/bin/env bash
# hc_analyze_data_cclyon.sh

debug=1

echo "Starting..." >&2

SW_PATH="/sps/nemo/scratch/golivier/software/Falaise/Analysis/sn_hc_simu_analysis/build/BuildProducts/bin"
SW_NAME="hc_analysis_data"

function usage(){
echo "--------------"
echo "Goal : Analyze half commissioning simulation data at cclyon"
echo "--------------"
echo "How to use it"
echo " "
echo "$ ./hc_analyze_data_cclyon.sh [OPTIONS] [ARGUMENTS]"
echo ""
echo "Allowed options: "
echo "-h  [ --help ]     produce help message"
echo "-n  [ --number ]   set the number of events"
echo "-r  [--run-number] set the run number to analyze"
echo "-C  [--calo-mapping] set the calo mapping rules for sorting"
echo "-T  [--tracker-mapping] set the tracker mapping rules for sorting"
echo " "
echo "./hc_analyze_data_cclyon.sh -r 0 -n number_of_events -C CALO_FILE -T TRACKER_FILE"
echo "Default value : number_of_events = 10"
echo " "
echo "--------------"
echo "Example : "
echo "./hc_analyze_data_cclyon.sh -n 100000 -r 0 -C CALO_FILE -T TRACKER_FILE"
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
echo "HC_TRACKER_MAPPING_CONFIG_FILE=" ${HC_TRACKER_MAPPING_CONFIG_FILE}

INPUT_RUN_DIR="/sps/nemo/scratch/golivier/half_commissioning_simu/damned_simu_${run_number}"
INPUT_SORTED_DIR="${INPUT_RUN_DIR}/sorted_data/match_rules"
INPUT_FILES=`ls -d ${INPUT_SORTED_DIR}/*.brio`

ANALYZED_OUTPUT_PATH="/sps/nemo/scratch/golivier/half_commissioning_simu/damned_simu_${run_number}/analyzed_data"
ANALYZED_ROOT_OUTPUT_PATH=${ANALYZED_OUTPUT_PATH}/root_files
ANALYZED_BRIO_OUTPUT_PATH=${ANALYZED_OUTPUT_PATH}/brio_files
LOG_DIR=${ANALYZED_OUTPUT_PATH}/log_files.d

file_counter=0

for file in ${INPUT_FILES}
do
    INPUT_FILENAME=`basename ${file} .brio` # .brio after basename $file remove extension of the input file
    INPUT_FILENAME=`basename ${INPUT_FILENAME} _sorted` # _sorted after basename $INPUT_FILENAME remove extension _sorted of the input file

    OUTPUT_CALO_TRACKER_FILENAME="output_calo_tracker_events.brio"
    OUTPUT_ROOT_FILE="output_rootfile.root"

    LOG_FILE=${LOG_DIR}/${INPUT_FILENAME}_analyzed.log

    echo "Mapping calo :" ${HC_CALO_MAPPING_CONFIG_FILE}
    echo "Mapping tracker :" ${HC_TRACKER_MAPPING_CONFIG_FILE}

    echo "Starting process..."
    echo "Processing..."

   ${SW_PATH}/${SW_NAME} -i ${file} -o ${ANALYZED_OUTPUT_PATH}/ -n $nb_event -C ${HC_CALO_MAPPING_CONFIG_FILE} -T ${HC_TRACKER_MAPPING_CONFIG_FILE} > ${LOG_FILE} 2>&1
    if [ $? -eq 1 ];
    then
	echo "ERROR : command ${SW_PATH}/${SW_NAME} -i ${file} -o ${ANALYZED_OUTPUT_PATH}/ -n $nb_event -C ${HC_CALO_MAPPING_CONFIG_FILE} -T ${HC_TRACKER_MAPPING_CONFIG_FILE} > ${LOG_FILE} 2>&1 FAILED !" >> ${LOG_FILE}
	echo "FILE_ANALYZING:FAILED" >> ${LOG_FILE}
	exit 0
    fi

    mv ${ANALYZED_OUTPUT_PATH}/${OUTPUT_CALO_TRACKER_FILENAME} ${ANALYZED_BRIO_OUTPUT_PATH}/${INPUT_FILENAME}_calo_tracker.brio
    if [ $? -eq 1 ];
    then
	echo "ERROR : mv ${ANALYZED_OUTPUT_PATH}/${OUTPUT_CALO_TRACKER_FILENAME} into ${ANALYZED_BRIO_OUTPUT_PATH}/${INPUT_FILENAME}_calo_tracker.brio FAILED !"
	exit 0
    fi

    mv ${ANALYZED_OUTPUT_PATH}/${OUTPUT_ROOT_FILE} ${ANALYZED_ROOT_OUTPUT_PATH}/${INPUT_FILENAME}_analyzed.root
    if [ $? -eq 1 ];
    then
	echo "ERROR : mv ${ANALYZED_OUTPUT_PATH}/${OUTPUT_ROOT_FILE} into ${ANALYZED_ROOT_OUTPUT_PATH}/${INPUT_FILENAME}_analyzed.root FAILED !"
	exit 0
    fi

    echo "FILE_ANALYZING:SUCCESS" >> ${LOG_FILE}
    let file_counter++

    echo "Ending process..."
done
