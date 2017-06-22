#!/usr/bin/env bash
# hc_analyse_data.sh

debug=1

echo "Starting..." >&2

SW_PATH="/home/goliviero/software/Falaise/Analysis/sn_hc_simu_analysis/build/BuildProducts/bin"
SW_NAME="hc_analysis_data"

function usage(){
echo "--------------"
echo "Goal : Analyze half commissioning simulation data"
echo "--------------"
echo "How to use it"
echo " "
echo "$ ./hc_analysis_data [OPTIONS] [ARGUMENTS]"
echo ""
echo "Allowed options: "
echo "-h  [ --help ]     produce help message"
echo "-n  [ --number ]   set the number of events"
echo "-r  [--run-number] set the run number to analyze"
echo " "
echo "./hc_analysis_raw_data.sh -n number_of_events"
echo "Default value : number_of_events = 10"
echo " "
echo "--------------"
echo "Example : "
echo "./hc_analysis_raw_data.sh -n 100000 -r 0"
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
INPUT_SORTED_DIR="${INPUT_RUN_DIR}/sorted_data/match_rules"
INPUT_FILES=`ls -d ${INPUT_SORTED_DIR}/*.brio`

ANALYZED_OUTPUT_PATH="${DATA_NEMO_PERSO_DIR}/half_commissioning_simu/run_${run_number}/analyzed_data"
ANALYZED_ROOT_OUTPUT_PATH=${ANALYZED_OUTPUT_PATH}/root_files
ANALYZED_BRIO_OUTPUT_PATH=${ANALYZED_OUTPUT_PATH}/brio_files
LOG_DIR=${ANALYZED_OUTPUT_PATH}/log_files.d

mkdir -p ${ANALYZED_OUTPUT_PATH} ${ANALYZED_ROOT_OUTPUT_PATH} ${ANALYZED_BRIO_OUTPUT_PATH} ${LOG_DIR}
if [ $? -eq 1 ];
then
    echo "ERROR : mkdir ${ANALYZED_OUTPUT_PATH} or ${ANALYZED_ROOT_OUTPUT_PATH} or ${ANALYZED_BRIO_OUTPUT_PATH} or ${LOG_DIR} FAILED !"
    exit 0
fi

HC_CALO_MAPPING_CONFIG_FILE=${INPUT_RUN_DIR}/hc_mapping/mapping_calo.conf
HC_TRACKER_MAPPING_CONFIG_FILE=${INPUT_RUN_DIR}/hc_mapping/mapping_tracker.conf

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
