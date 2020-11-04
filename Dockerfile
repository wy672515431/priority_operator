FROM alpine
RUN apk add --no-cache g++
WORKDIR /app/
COPY ./* ./
RUN  g++ test.cpp -o test
RUN chmod +x test