FROM alpine:3.6

# nginxのインストール
RUN apk update && \
    apk add --no-cache nginx

# ドキュメントルート
ADD app-root /app-root
ADD default.conf /etc/nginx/conf.d/default.conf

# ポート設定
EXPOSE 80
EXPOSE 443

RUN mkdir -p /run/nginx

# フォアグラウンドでnginx実行
CMD nginx -g "daemon off;"
