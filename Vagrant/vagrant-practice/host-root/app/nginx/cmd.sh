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
      docker run -d ${opt_port} --name ${DOCKER_CONTAINER_NAME} ${DOCKER_IMAGE_NAME}
      ;;

    # 起動中のコンテナでシェル実行
    'sh' )
      echo \# ${OPT}
      docker exec -it ${DOCKER_CONTAINER_NAME} ${SHELL_CMD}
      ;;

    # 起動中のコンテナを停止＆削除
    'stop' )
      echo \# ${OPT}
      docker stop $(docker ps -a -q --filter ancestor=${DOCKER_CONTAINER_NAME} --format="{{.ID}}")
    docker rm $(docker ps -a -q --filter ancestor=${DOCKER_CONTAINER_NAME} --format="{{.ID}}")
      ;;

    # 未対応コマンドエラー
    * )
      echo "Error: Unknown command named '${OPT}'." >&2
      exit 1
      ;;
      
  esac
  shift
done

#------------------------------------------------------------------------------
# EOF
