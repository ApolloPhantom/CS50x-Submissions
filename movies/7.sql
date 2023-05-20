select m.title,r.rating from movies as m,ratings as r where m.year = 2010 and
m.id = r.movie_id order by r.rating desc,m.title asc;