-- shanghai exchange market tick data
CREATE DATABASE sh_tick_md;

-- shenzheng exchange market
CREATE DATABASE sz_tick_md;

USE sh_tick_md;

CREATE TABLE IF NOT EXISTS 20250416 
(
    `time` DateTime COMMENT 'market_data::action_time',
    `ms` Int16 COMMENT 'market_data::action_ms',
    `date` Date COMMENT 'market_data::trading_day',
    `name` String COMMENT 'market_data::instrument_name',
    `code` String COMMENT 'market_data::instrument_id',
    `open_price` Float32 COMMENT 'market_data::open_price',
    `pre_close_price` Float32 COMMENT 'market_data::pre_close_price',
    `price` Float32 COMMENT 'market_data::settlement_price',
    `high_price` Float32 COMMENT 'market_data::highest_price',
    `low_price` Float32 COMMENT 'market_data::lowest_price',
    `volume` Float32 COMMENT 'market_data::volume',
    `amount` Float32 COMMENT 'market_data::turnover',
    `bid_volumn1` Float32 COMMENT 'market_data::bid_volumn1',
    `bid_price1` Float32 COMMENT 'market_data::bid_price1',
    `bid_volumn2` Float32 COMMENT 'market_data::bid_volumn2',
    `bid_price2` Float32 COMMENT 'market_data::bid_price2',
    `bid_volumn3` Float32 COMMENT 'market_data::bid_volumn3',
    `bid_price3` Float32 COMMENT 'market_data::bid_price3',
    `bid_volumn4` Float32 COMMENT 'market_data::bid_volumn4',
    `bid_price4` Float32 COMMENT 'market_data::bid_price4',
    `bid_volumn5` Float32 COMMENT 'market_data::bid_volumn5',
    `bid_price5` Float32 COMMENT 'market_data::bid_price5',
    `ask_volumn1` Float32 COMMENT 'market_data::ask_volumn1',
    `ask_price1` Float32 COMMENT 'market_data::ask_price1',
    `ask_volumn2` Float32 COMMENT 'market_data::ask_volumn2',
    `ask_price2` Float32 COMMENT 'market_data::ask_price2',
    `ask_volumn3` Float32 COMMENT 'market_data::ask_volumn3',
    `ask_price3` Float32 COMMENT 'market_data::ask_price3',
    `ask_volumn4` Float32 COMMENT 'market_data::ask_volumn4',
    `ask_price4` Float32 COMMENT 'market_data::ask_price4',
    `ask_volumn5` Float32 COMMENT 'market_data::ask_volumn5',
    `ask_price5` Float32 COMMENT 'market_data::ask_price5'
) 
ENGINE =MergeTree() 
PRIMARY KEY (time) 
ORDER BY (time, ms);