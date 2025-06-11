SELECT 
        DATE,
        HIGH,
        LOW,
        OPEN,
        CLOSE,
        VOLUME
FROM {SCHEMA}.T_SPY
WHERE DATE BETWEEN ? AND ?
ORDER BY DATE asc;
