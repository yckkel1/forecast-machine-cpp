SELECT 
        DATE,
        HIGH,
        LOW,
        OPEN,
        CLOSE,
        VOLUME
FROM {SCHEMA}.T_NDQ
WHERE DATE BETWEEN ? AND ?
ORDER BY DATE asc;
