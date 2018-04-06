# 文字コード:UTF-8

FROM node

RUN mkdir /app
COPY . /app
RUN ls -l /app
RUN cd /app; npm install --save express
RUN cd /app; npm install --save socket.io
RUN cd /app; npm install --save jade
EXPOSE 5000
CMD ["node", "/app/app.js"]
