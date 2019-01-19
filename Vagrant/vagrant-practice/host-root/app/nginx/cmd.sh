#!bash
set -eu

#------------------------------------------------------------------------------
# 環境設定ロード
base_dir="$(dirname "$0")"
source "${base_dir}/env.sh"

#------------------------------------------------------------------------------
# コマンド実行
for OPT in "$@"
do
  case $OPT in
    'run' )
      echo \# ${OPT}
      docker build . -t ${DOCKER_IMAGE_NAME}
      docker run -d -p 80:80 -p 443:443 --name ${DOCKER_CONTAINER_NAME} ${DOCKER_IMAGE_NAME}
      ;;
    'stop' )
      echo \# ${OPT}
      docker stop $(docker ps -a -q --filter ancestor=${DOCKER_CONTAINER_NAME} --format="{{.ID}}")
    docker rm $(docker ps -a -q --filter ancestor=${DOCKER_CONTAINER_NAME} --format="{{.ID}}")
      ;;
  esac
  shift
done

#------------------------------------------------------------------------------
# EOF
