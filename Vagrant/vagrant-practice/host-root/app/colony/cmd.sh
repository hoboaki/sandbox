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
    # イメージをビルド＆コンテナを起動
    'run' )
      echo \# ${OPT}

      opt_port=""
      if [ -v DOCKER_PORTS ]; then
        for p in ${DOCKER_PORTS[@]}; do
          opt_port="${opt_port} -p ${p}"
        done
      fi

      docker build . -t ${DOCKER_IMAGE_NAME}
      docker run -it ${opt_port} --name ${DOCKER_CONTAINER_NAME} ${DOCKER_IMAGE_NAME}  /bin/ash
      # docker exec -it ${DOCKER_CONTAINER_NAME} /bin/ash
      ;;

    # 起動中のコンテナを停止＆削除
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
