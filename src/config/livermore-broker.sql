-- cmd: clickhouse-client --multiquery < livermore-broker.sql

-- shanghai/shenzheng exchange market tick data all in one
CREATE DATABASE IF NOT EXISTS tick;

USE tick;

CREATE TABLE IF NOT EXISTS {tick_table_name}
(
    `action_time` DateTime COMMENT 'market_data::action_time',
    `action_ms` Int16 COMMENT 'market_data::action_ms',
    `trading_day` Date COMMENT 'market_data::trading_day',
    `name` String COMMENT 'market_data::instrument_name',
    `code` String COMMENT 'market_data::instrument_id',
    `open_price` Float32 COMMENT 'market_data::open_price',
    `pre_close_price` Float32 COMMENT 'market_data::pre_close_price',
    `price` Float32 COMMENT 'market_data::settlement_price',
    `high_price` Float32 COMMENT 'market_data::highest_price',
    `low_price` Float32 COMMENT 'market_data::lowest_price',
    `volume` Float32 COMMENT 'market_data::volume',
    `amount` Float32 COMMENT 'market_data::turnover',
    `bid_volume1` Float32 COMMENT 'market_data::bid_volume1',
    `bid_price1` Float32 COMMENT 'market_data::bid_price1',
    `bid_volume2` Float32 COMMENT 'market_data::bid_volume2',
    `bid_price2` Float32 COMMENT 'market_data::bid_price2',
    `bid_volume3` Float32 COMMENT 'market_data::bid_volume3',
    `bid_price3` Float32 COMMENT 'market_data::bid_price3',
    `bid_volume4` Float32 COMMENT 'market_data::bid_volume4',
    `bid_price4` Float32 COMMENT 'market_data::bid_price4',
    `bid_volume5` Float32 COMMENT 'market_data::bid_volume5',
    `bid_price5` Float32 COMMENT 'market_data::bid_price5',
    `ask_volume1` Float32 COMMENT 'market_data::ask_volume1',
    `ask_price1` Float32 COMMENT 'market_data::ask_price1',
    `ask_volume2` Float32 COMMENT 'market_data::ask_volume2',
    `ask_price2` Float32 COMMENT 'market_data::ask_price2',
    `ask_volume3` Float32 COMMENT 'market_data::ask_volume3',
    `ask_price3` Float32 COMMENT 'market_data::ask_price3',
    `ask_volume4` Float32 COMMENT 'market_data::ask_volume4',
    `ask_price4` Float32 COMMENT 'market_data::ask_price4',
    `ask_volume5` Float32 COMMENT 'market_data::ask_volume5',
    `ask_price5` Float32 COMMENT 'market_data::ask_price5'
) ENGINE =MergeTree() PARTITION BY toYYYYMMDD(trading_day) ORDER BY (action_time, action_ms);