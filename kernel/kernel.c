void			main()
{
	void		*video_memory = (void *)0xb8000;

	*((char *)video_memory) = 'X';
}
