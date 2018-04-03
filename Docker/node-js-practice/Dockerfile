# 文字コード:UTF-8

FROM node

RUN mkdir /app
COPY . /app
RUN ls -l /app
RUN cd /app; npm install --save express
RUN cd /app; npm install --production

EXPOSE 5000
CMD ["node", "/app/index.js"]
