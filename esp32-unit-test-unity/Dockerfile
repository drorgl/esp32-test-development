FROM ubuntu:20.04

RUN apt update && apt install -y python3 curl python3-venv gcc g++

RUN python3 -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/master/scripts/get-platformio.py)"

ENV PATH="${PATH}:/root/.platformio/penv/bin"

RUN pio settings set check_platformio_interval 0
RUN pio settings set enable_telemetry No

WORKDIR  /app

COPY platformio.ini /app

RUN pio run; exit 0
RUN pio check; exit 0

COPY . /app

RUN pio run

# RUN pio test -e native --junit-output
RUN pio check


