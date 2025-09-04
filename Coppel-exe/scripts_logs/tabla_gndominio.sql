--solo usar de manera local

create table gndominio(
	tienda smallint,
	ciudad smallint,
	fecha date DEFAULT now()
);

SELECT * FROM gndominio;

-- insert into gndominio (tienda, ciudad) values (803, 4);