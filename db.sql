CREATE TYPE tag_type as ENUM ('Mifare_Classic', 'Mifare_Plus', 'Mifare_UL', 'FeliCa', 'Topaz_Jewel', 'Em_Marin', 'QR_Code', 'Bar_Code');

CREATE TABLE accounting.label (id serial, type tag_type default 'Mifare_Classic'::tag_type NOT NULL, data bytea NOT NULL, PRIMARY KEY (id));
CREATE TABLE accounting.client (id serial NOT NULL, name varchar UNIQUE NOT NULL, label_id INTEGER, PRIMARY KEY (id), FOREIGN KEY (label_id) REFERENCES label (id) ON UPDATE CASCADE);

### SELECT p.relname, e.moment, e.label_id FROM accounting.event e, pg_class p WHERE e.tableoid = p.oid AND label_id = 0; ###
CREATE TABLE accounting.event (moment timestamp NOT NULL DEFAULT now(), label_id INTEGER NOT NULL, PRIMARY KEY (moment), FOREIGN KEY (label_id) REFERENCES accounting.label (id) ON UPDATE CASCADE);
CREATE TABLE accounting.trigger () INHERITS (accounting.event);
CREATE TABLE accounting.payment (cash money) INHERITS (accounting.event);
CREATE TABLE accounting.mode (tariff money) INHERITS (accounting.event);
CREATE TABLE accounting.reset () INHERITS (accounting.event);

CREATE OR REPLACE FUNCTION last_label_payment(id INTEGER) RETURNS money AS $payment_sum$
    DECLARE last_payment_reset timestamp;
    DECLARE payment_sum money;
BEGIN
    SELECT max(moment) FROM accounting.reset WHERE label_id = id INTO last_payment_reset;
    SELECT sum(cash) FROM accounting.payment WHERE label_id = id AND moment > last_payment_reset INTO payment_sum; RETURN payment_sum;
END;
$payment_sum$ LANGUAGE plpgsql;
